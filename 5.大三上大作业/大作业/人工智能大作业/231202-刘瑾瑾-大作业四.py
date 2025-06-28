import torch
from torch import nn
from d2l import torch as d2l
from matplotlib import pyplot as plt
from torch.optim import lr_scheduler
from torch.optim.lr_scheduler import ExponentialLR
from torchvision import transforms
from PIL import Image
def vgg_block(num_convs, in_channels, out_channels):
    layers = []
    for _ in range(num_convs):
        layers.append(nn.Conv2d(in_channels, out_channels,
                                kernel_size=3, padding=1))
        layers.append(nn.BatchNorm2d(out_channels))
        layers.append(nn.ReLU())
        in_channels = out_channels
    layers.append(nn.MaxPool2d(kernel_size=2, stride=2))
    return nn.Sequential(*layers)

conv_arch = ((1, 64), (1, 128), (2, 256), (2, 512), (2, 512))

def vgg(conv_arch):
    conv_blks = []
    in_channels = 3
    # 卷积层部分
    for (num_convs, out_channels) in conv_arch:
        conv_blks.append(vgg_block(num_convs, in_channels, out_channels))
        in_channels = out_channels

    return nn.Sequential(
        *conv_blks, nn.Flatten(),
        # 全连接层部分
        nn.Linear(out_channels * 3 * 3, 4096), nn.ReLU(), nn.Dropout(0.4),
        nn.Linear(4096, 4096), nn.ReLU(), nn.Dropout(0.4),
        nn.Linear(4096, 10))

net = vgg(conv_arch)

X = torch.rand(size=(1, 3, 112, 112), dtype=torch.float32)
for layer in net:
    X = layer(X)
    print(layer.__class__.__name__,'output shape: \t',X.shape)

ratio = 4
small_conv_arch = [(pair[0], pair[1] // ratio) for pair in conv_arch]
net = vgg(small_conv_arch)


def evaluate_accuracy_gpu(net, data_iter, device=None): #@save
    """使用GPU计算模型在数据集上的精度"""
    if isinstance(net, nn.Module):
        net.eval()  # 设置为评估模式
        if not device:
            device = next(iter(net.parameters())).device
    # 正确预测的数量，总预测的数量
    metric = d2l.Accumulator(2)
    with torch.no_grad():
        for X, y in data_iter:
            if isinstance(X, list):
                X = [x.to(device) for x in X]
            else:
                X = X.to(device)
            y = y.to(device)
            metric.add(d2l.accuracy(net(X), y), y.numel())
    return metric[0] / metric[1]

#@save
def train_ch6(net, train_iter, test_iter, num_epochs, device, loss, optimizer, scheduler=None):
    def init_weights(m):
        if isinstance(m, nn.Conv2d):
            nn.init.kaiming_normal_(m.weight, mode="fan_out")
            if m.bias is not None:
                nn.init.zeros_(m.bias)
        elif isinstance(m, (nn.BatchNorm2d, nn.GroupNorm)):
            nn.init.ones_(m.weight)
            nn.init.zeros_(m.bias)
        elif isinstance(m, nn.Linear):
            nn.init.normal_(m.weight, 0, 0.01)
            nn.init.zeros_(m.bias)
    net.apply(init_weights)
    print('training on', device)
    net.to(device)
    animator = d2l.Animator(xlabel='epoch', xlim=[1, num_epochs],
                            legend=['train loss', 'train acc', 'test acc'])
    timer, num_batches = d2l.Timer(), len(train_iter)
    for epoch in range(num_epochs):
        # 训练损失之和，训练准确率之和，样本数
        print("epoch = {}, scheduler = {}".format(epoch, scheduler.get_last_lr()[0]))
        metric = d2l.Accumulator(3)
        net.train()
        for i, (X, y) in enumerate(train_iter):
            timer.start()
            optimizer.zero_grad()
            X, y = X.to(device), y.to(device)
            y_hat = net(X)
            l = loss(y_hat, y)
            # print("第一个l{}".format(l))
            l.backward()
            optimizer.step()
            with torch.no_grad():
                metric.add(l * X.shape[0], d2l.accuracy(y_hat, y), X.shape[0])
                # print("X.shape{}".format(X.shape[0]))
            timer.stop()
            # print("metric[0]{}".format(metric[0]))
            # print("metric[2]{}".format(metric[2]))
            train_l = metric[0] / metric[2]
            # print("train_ls{}".format(train_l))
            train_acc = metric[1] / metric[2]
            if (i + 1) % (num_batches // 5) == 0 or i == num_batches - 1:
                animator.add(epoch + (i + 1) / num_batches,
                             (train_l, train_acc, None))
        test_acc = evaluate_accuracy_gpu(net, test_iter)
        animator.add(epoch + 1, (None, None, test_acc))
        if scheduler:
            if scheduler.__module__ == lr_scheduler.__name__:
                # UsingPyTorchIn-Builtscheduler
                scheduler.step()
            else:
                # Usingcustomdefinedscheduler
                for param_group in optimizer.param_groups:
                    param_group['lr'] = scheduler(epoch)
    plt.show()
    torch.save(net.state_dict(), 'net.pt')
    print(f'loss {train_l:.3f}, train acc {train_acc:.3f}, '
          f'test acc {test_acc:.3f}')
    print(f'{metric[2] * num_epochs / timer.sum():.1f} examples/sec '
          f'on {str(device)}')
def get_ciffa_labels(labels):  #@save
    """返回ciffar数据集的文本标签"""
    text_labels = ['airplane', 'automobile', 'bird', 'cat', 'deer',
                   'dog', 'frog', 'horse', 'ship', 'truck']
    return [text_labels[int(i)] for i in labels]

if __name__ == '__main__':
    lr, num_epochs, batch_size = 0.1, 20, 128
    optimizer = torch.optim.SGD(net.parameters(), momentum=0.9, lr=lr, weight_decay=1e-3)
    loss = nn.CrossEntropyLoss()
    scheduler = ExponentialLR(optimizer, gamma=0.9)
    train_iter, test_iter = d2l.load_data_ciffar_10(batch_size, resize=112)
    # train_ch6(net, train_iter, test_iter, num_epochs, d2l.try_gpu(), loss, optimizer, scheduler)

    m_stat_dict = torch.load('net.pt')
    new_net = net
    new_net.load_state_dict(m_stat_dict)
    img = Image.open('./kache.jpg')
    transform = transforms.ToTensor()
    img_1 = transform(img)
    img_1 = torch.unsqueeze(img_1, 0)
    y_hat = new_net(img_1)
    print(y_hat)
    y_hat = d2l.argmax(y_hat, axis=1)
    print("预测结果为{}".format(get_ciffa_labels(y_hat)))