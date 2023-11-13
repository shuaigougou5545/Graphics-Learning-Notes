# Real-Time Rendering

### Chapter 1 - 介绍

- 帧率（fps）：电脑主机每秒发送到显示器的图像数量【PC】
- 刷新率（hz）：显示器实时显示这些帧的速度【显示器】

规范：

- 本书采用**右手坐标系**进行讲解

### Chapter 2 - 图形渲染管线

#### （1）渲染管线

渲染管线：应用阶段、几何处理、光栅化阶段、像素处理

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311071102093.png" alt="截屏2023-11-07 11.02.14" style="zoom:50%;" />

#### （2）应用阶段

应用阶段在CPU上执行，优化这个阶段能影响后续渲染管线的性能。比如我们可以在CPU上实现**剔除算法（Culling Algorithm）**，以减少需要被渲染的三角形数目；当然应用阶段不一定只能在CPU上执行，**也可以利用GPU（比如计算着色器）**

应用阶段最重要的作用是准备渲染图元数据（rendering primitives）

#### （3）几何处理

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202311071120047.png" alt="截屏2023-11-07 11.20.50" style="zoom:50%;" />

Vertex Shading：计算顶点的位置，并计算后续可能用到的顶点属性，比如法线、纹理坐标等，还能进行逐顶点的一些操作，比如顶点动画

Local => World => View

