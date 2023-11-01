# DirectX 12 

#### 1.数学库

**DirectXMath**库，支持SIMD指令，借助单指令多数据，可以进行多分量同时计算

#### 2.前置知识

##### （1）组件对象模型 - COM

COM是一种软件架构模型，在DirectX 12中，COM用于创建各种不同类型的对象，比如设备(device)、交换链(swap chain)以及各种资源。<font color='green'>**COM接口都以大写字母“I”作为开头**</font>，比如`ID3D12GraphicsCommandList`。

在此，我们不需要细究COM的设计原理，只需要会使用即可。微软有Windows运行时库，提供`Microsoft::MRL::ComPtr`类，我们可以把它当作COM对象的智能指针，当Comptr实例超过作用域范围时，会自动调用Release方法，在此我们需要知道另外三个常用的方法：

- `Get()`：返回指向COM的指针
- `GetAddressOf()`：返回COM对象指针的指针，比如说你想要重新让指针指向一个新的COM对象
- `Reset()`：相当于调用Release并将指针置为nullptr

##### （2）纹理格式

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311012053332.png" alt="截屏2023-11-01 20.53.12" style="zoom:50%;" />

规律：

- 数字就是该分量所占位数(bit数)
- 符号：
  - UNORM：(unsigned normalized) 范围[0,1]
  - SNORM：(signed normalized) 范围[-1,1]
  - FLOAT、UINT、SINT等

##### （3）交换链 - swap chain

双缓冲、三重缓冲等策略完成渲染展示

交换链：`IDXGISwapChain`

方法：

- `IDXGISwapChain::ResizeBuffers`：修改缓冲区大小 => 这里修改的是窗口缓冲区的大小，并不是视口的大小
- `IDXGISwapChain::Present`：呈现缓冲区内容，交换前后台缓冲区 => **相当于OpenGL中`glSwapBuffers(window)`**

##### （4）深度缓冲

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311012103741.png" alt="截屏2023-11-01 21.03.50" style="zoom:50%;" />

只要使用模版缓冲区，则必须使用深度缓冲区，深度缓冲区总是与模版缓冲区“如影随形，共同进退”，一般使用`DXGI_FORMAT_D24_UNORM_S8_UINT`

##### （5）资源与描述符

**描述符/视图**：对送往GPU的资源进行描述的一种轻量级结构

常用的描述符：

- CBV、SRV、UAV：常量缓冲区视图、着色器资源视图、无序访问视图
- sampler：采样器描述符
- RTV：渲染目标视图
- DSV：深度模版视图

```cpp
在OpenGL中没有描述符这种概念，有对象(Object)的概念，比如纹理对象、帧缓冲对象、顶点数组对象、UBO等
```

**描述符堆**：存放特定类型描述符的一块内存

描述符创建的最佳时期是在初始化期间，因为会执行额外的检验和验证工作，最好不要在运行时创建描述符 => “在资源创建的伊始就应当确定它的具体格式”

##### （6）SSAA、MSAA

SSAA、4X MSAA：都同样使用4倍于屏幕分辨率的后台缓冲区和深度缓冲区，但SSAA的像素处理数量依旧是四倍

D3D多重采样：使用`DXGI_SAMPLE_DESC`，涉及采样点数量（比如1或者4）、以及质量(硬件厂商可能提供高级的抗锯齿等算法、采样模式以及权重)

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311012127452.png" alt="截屏2023-11-01 21.27.28" style="zoom:50%;" />

PS：我们做之前，可以通过一些接口去查询当前硬件支持的最大额度

MSAA能直接影响缓冲区大小，所以我们不管是填写交换链缓冲区、深度缓冲区时，都要填写`DXGI_SAMPLE_DESC`，且我们一定要保持一致

##### （7）功能级别

DirectX会将不同大小版本(从dx9开始)，打包成一个个功能集，如果一个硬件能完全支持功能集中所有特性，则会记录当前硬件的功能级别。开发者在开发过程中，可以查询硬件所支持的功能级别，就能对应完成开发。

##### （8）DirectX图形基础结构 - DXGI

设计DXGI的基本理念是，将多种图形API中所共有的底层能力，借助一组通用的API来进行处理 => 包括：交换链、页面翻转、切换窗口模式、显示模式以及窗口相关(分辨率、刷新率)等，它们在2D和3D之间都是通用的

##### （9）资源滞留

<font color='red'>**DirectX 12中，应用程序可以控制资源在显存中的去留，主动管理资源的去留情况 => DirectX11中是由系统自动管理**</font>

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311012156324.png" alt="截屏2023-11-01 21.56.07" style="zoom: 43%;" />

#### 3.CPU和GPU间的交互

##### （1）命令队列和命令列表

GPU维护一个命令队列(一般是环形缓冲区)，CPU通过命令列表将命令提交到这个队列中去

**命令队列**：`ID3D12CommandQueue`，通过`ID3D12Device::CreateCommandQueue`方法创建队列

**命令列表**：`ID3D12CommandQueue::ExecuteCommandLists()`将命令列表中的命令添加到命令队列中去，参数是指令数目，以及命令列表的首指针；命令列表<font color='green'>**`ID3D12GraphicsCommandList`**</font>接口封装了一系列的图形渲染命令，它继承于`ID3D12CommandList`，提供很多种方式向命令列表中添加命令队列

```cpp
ID3D12GraphicsCommandList的相关函数，其实在OpenGL中对应的就是gl...函数，比如glViewport、glDrawArrays等
```

不同于OpenGL的是，这里只是将命令添加进命令队列中，并没有立马执行，还需要调用Close()函数结束记录命令，并调用`ExecuteCommandLists()`将命令发送至命令队列

**命令分配器**（Command Allocator）：命令列表是一种抽象的表达【或者说是一种逻辑容器】，实际命令是存储在命令分配器中，可以看作一个命令内存池

命令列表的类型：

- `D3D12_COMMAND_LIST_TYPE_DIRECT`：一系列可供GPU直接执行的命令
- `D3D12_COMMAND_LIST_TYPE_BUNDLE`：将命令列表打包，打包完成后驱动会对里面的一系列命令进行预处理，让在渲染过程中执行得到优化 => 优势：如果一组命令经常一起出现，我们可以将它打包在一起，提高**复用性**，提高CPU性能 => 使用`ExecuteBundle()`将命令嵌入直接命令列表中

##### （2）CPU和GPU间的同步

在CPU和GPU的同步问题中，我们会遇到脏读等情况，我们往往需要强制CPU等待，直到GPU完成所有命令的处理，达到某个指定的围栏点为止 => 这种操作叫做刷新命令队列

**围栏**（Fence）的使用：

```cpp
// 提交命令列表并更新fence值
m_commandQueue->ExecuteCommandLists(1, commandLists); // 提交命令到命令队列
m_fenceValue++;
m_commandQueue->Signal(m_fence.Get(), m_fenceValue); 
// 在CPU上等待Fence
if(m_fence->GetCompletedValue() < m_fenceValue)
{
		// 处理事件
  	Wait...
}
```

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311012245351.png" alt="截屏2023-11-01 22.45.49" style="zoom:40%;" />

##### （3）资源转换

GPU通常会对某个资源按顺序执行先写后读的操作，当GPU的写操作还没有完成时，却开始读资源，这会导致**资源冒险**。所以DirectX为资源设计了一组相关状态，当要写资源时，我们会将它的状态转换为**渲染目标状态**；当要读资源时，我们将它的状态变为**着色器资源状态**

<font color='green'>**DirectX11中资源转换的工作交由驱动自动管理，会让性能变差，DirectX12中将这项工作交给程序员手动管理**</font>

**转换资源屏障**：通过命令列表设置转换资源屏障，可以通过一次API调用转换多个资源的状态 =>比如： `mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));`  从呈现状态转换到渲染目标状态

##### （4）命令与多线程

命令列表是一种发挥Direct3D多线程优势的设计，我们可以通过创建多个线程，分别创建一个命令列表，来绘制场景中一部分的物体

注意，这里有一些需要强调的理解：

- 命令列表并不是自由线程对象：也就是说并不能多个线程去共享同一个命令列表，而是单个线程去管理自己的命令列表
- 命令分配器也不是自由线程对象：每个线程独有自己的命令分配器
- 命令队列是线程自由对象：多个线程可以访问GPU上同一个命令队列，就是每个线程可以同时向命令队列提交它们存储在命令列表中的命令 => 互斥锁等实现线程自由

#### 4.Direct3D流水线

----

#### 拓展：

DirectX 12相比于DirectX 11的区别：

- **资源滞留**：程序员可以手动控制资源在显存中的去留，DX11中由驱动程序和运行时自动管理
- **资源转换**：程序员手动控制资源的状态转换，DX11由驱动自动管理