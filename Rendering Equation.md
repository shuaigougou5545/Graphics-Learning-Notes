# Rendering Equation

💡本文的顺序：介绍辐射度量学（为引入渲染方程打下基础），介绍渲染方程，通过渲染方程理解常见的图形学算法

### 1.Radiometry - 辐射度量学

#### （1）Radiant Energy and Flus（Power）

**Radiant energy**：the energy of electromagnetic radiation.It is measured in units of joules

辐射能：辐射的能量，以焦耳为单位
$$
Q[J=Joule]
$$
**Radiant flux/power**：the energy emitted, reflected, transmitted or received, per unit time

辐射通量/辐射功率：每单位时间释放、反射、透射或接受的能量，以瓦特或流明为单位
$$
\phi \equiv \frac{dQ}{dt}[W=Watt][lm=lumen]
$$

光是有能量的，在单位时间内光源发出或者平面接受的能量，就是辐射通量

#### （2）Radiant Intensity

**Radiant Intensity**：the power per unit **solid angle** emitted by a point light source

辐射强度：每单位立体角由点光源发出的功率【注意：就是上图中第1个】
$$
I(\omega)\equiv \frac{d\Phi}{d\omega}
\\ [\frac{W}{sr}][\frac{lm}{sr}=cd=candela]
$$
所以，如果一个点光源能够均匀向外散射能量，那么：
$$
I(\omega)_{point\_light}=\frac{\Phi}{4\pi}
$$

#### （3） Irradiance 

<font color='red'>**Irradiance（E，辐照度）**</font>：the power per unit area incident on a surface point

辐照度的含义是：某个表面在单位面积上接受到的辐射通量，所以说dA并不是一个可变的量（不是说这个表面面积越大，dA就越大）
$$
E(x)\equiv\frac{d\Phi(x)}{dA}
\\ [\frac{W}{m^2}][\frac{lm}{m^2}=lux]
$$
但是不是也可以写成：也就是总磁通量除以总面积
$$
E(x)=\frac{\Phi(x)}{A}
$$
注意：**这里dA代表的是单位照射面积，而不是垂直于入射光线的投影面积**「Irradiance和radiance公式中的dA是等价的」

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308282243901.png" alt="截屏2023-08-28 22.43.14" style="zoom:30%;" />

注意：👆上图中，这个cosθ实际上是乘在Φ旁边的，而不是A旁边的。我们可以这样理解：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308302045323.png" alt="截屏2023-08-30 20.44.51" style="zoom:25%;" />

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308302045392.png" alt="截屏2023-08-30 20.44.51" style="zoom:25%;" />

图1：光线垂直射向面积为A1的平面，我们将辐射通量看成一根根光线，假设一单位面积有n根光线，那么A1能接收到A1\*n根光线；图2：光线斜着射向平面，光线与平面法线的夹角为theta，那么实际上他接受不了A2\*n跟光线，而是(A2\*cosθ)*n根光线；我们能看到，当斜着射向平面时，平面所接收到的辐射通量是有衰减的 

=> 这就是朗伯余弦定理，一般我们认为光通量(radiance flux)是有方向性的，它也许不是单一方向，但是它每根光线都有它对应的方向，**所以我们需要分析平面能接收到的所有光线，并计算垂直于光线方向的平面**

所以我们再回看公式：
$$
E(x)=\frac{d\Phi(x)}{dA}
$$
E(x)：x代表平面的位置，E(x)是指x位置处的辐照度，其中平面面积为dA，接收到的辐射通量为dΦ(x)；也就是单位时间内，通过dA的光能量

这里的dΦ(x)要注意，根据我们上面的推理，这里的dΦ(x)应该等于：
$$
d\Phi(x)=\int d\Phi(x,\omega_i)·cosθ \ d\omega_i
\\ E=\frac{d\Phi(x)}{dA}=\frac{\int d\Phi(x,\omega_i)·cosθ \ d\omega_i}{dA}
\\ 假设:各个方向的磁通量相同
\\ E=\frac{d\Phi(x,\omega_i)\cdot \sum cosθ\cdot \int d\omega_i}{dA}=\frac{d\Phi(x,\omega_i)\cdot \int d\omega_i}{dA}\cdot \sum cosθ
\\ 
$$
对于方向光：
$$
\\ 方向光:d\Phi(x)=d\Phi(x,\omega_i)·cosθ
\\ E=\frac{d\Phi(x)}{dA}=\frac{d\Phi(x,\omega_i)}{dA}·cosθ
$$
根据式子，我们明白了这个cosθ是从何而来，现在我们建立了E与Σcosθ的关系，如果细心我们可以发现另一个式子：dA·Σcosθ=垂直于光方向的投影面积，所以说，垂直于光方向的投影面积与E之间的关系是成正比的

我们以这个图为例：解释为什么是垂直于光方向的投影面积

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308302343901.png" alt="截屏2023-08-30 23.43.06" style="zoom:40%;" />

所以👇图中，最上面的实心弧线越长，在其他条件不变的情况下，irradiance(E)越大

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308302053644.png" alt="截屏2023-08-30 20.52.57" style="zoom:40%;" />



🌟联想到： 

- 朗伯余弦定理，也就解释的通了，我们之前在blinnphong中所涉及的<font color='green'>**光的强度，实际上就是Irradiance**</font>；实际上当平面不垂直于光线时，所获取到的光线条数(辐射通量)就会变少
- 同时，blinnphong模型中的点光源会根据距离进行衰减，如果光的强度是Intensity，按道理来说是不衰减的，因为是flux/单位立体角，单位立体角可以延伸出去；所以再次证明，<font color='green'>**光的强度，实际上就是Irradiance**</font>，因为点光源向四周发射，那么垂直于光的面积就是球的表面积4πr<sup>2</sup>，所以光是按照距离的平方进行衰减
  - 是因为光源发出的总能量是不变的，但总面积增大了，根据公式2


#### （4）Radiance

**Radiance**（L ）：the power emitted reflected transmitted or received by a surface，per unit solid angle，per projected unit area

辐射度(亮度)：每单位立体角和每单位投影面积上，由表面反射、发射或接收的能量。
$$
L(p,\omega)\equiv\frac{d^2\Phi(p,\omega)}{d\omega \ dA \ cos\theta}
$$
公式中dAcosθ就是垂直于光线的面积{注意：irradiance和radiance中的dA的定义其实是不一样的，irradiance中dA是表示的垂直面积，而radiance中的dA表示的是接受平面}

radiance的实际含义就是：该单位面积的平面，接收到从某一个方向来的光，是多少

```
所以，对于一个平面所接收到的光照的计算，我们可以拆成许多微平面，每个微平面又能从四面八方接受能量，所以要对角度和面积进行积分，能够得到所有的光照
```

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308282259370.png" alt="截屏2023-08-28 22.59.01" style="zoom:30%;" />



irradiance & radiance 的关系：
$$
dE(p,\omega)=L_i(p,\omega)cos\theta\ d\omega
\\ E(p)=\int_{H^2}L_i(p,\omega)cos\theta\ d\omega
$$

#### （5）BRDF - Bidirectional Reflectance Distribution Function

brdf：radiance from direction wi turns into the power E that dA receives，Then power E will become the radiance to any other direction wo

也就是radiance的积分，作为dA表面接收到的能量E，然后又朝特定方向发射radiance

注意：这里是wi方向入射的irradiance，与wr方向出射的radiance之比，也就是说，brdf有两个参数，入射方向和出射方向
$$
f_r(\omega_i\rightarrow\omega_r)=\frac{dL_r(\omega_r)}{dE_i(\omega_i)}=\frac{dL_r(\omega_r)}{L_i(\omega_i)cos\theta_id\omega_i}
$$

```cpp
为什么入射会选择irradiance,而出射选择radiance,可以这么理解:
入射的意思是光线打到平面上，且平面要吸收能量，那radince其实不能代表吸收能量这层含义，因为还要乘上平面与法线的夹角，也就是朗伯余弦定理，而irradiance就能代表这层含义
但是irradiance的表示中没有立体角，因为irradiance是表示通过该平面的所有磁通量，那么只来自于一个方向wi的磁通量，在这里只能表示为dE
另外,我们会发现dE=Lcos(theta)dw，就有朗伯余弦定理
```

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308292105087.png" alt="截屏2023-08-29 21.05.44" style="zoom:40%;" />

入射方向：我们需要求到达该平面的irradiance(E)

### 2.渲染方程

#### （1）rendering equation

$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{H^2}L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$

```
渲染方程：渲染方程是计算着色点p朝着wo发射出的radiance
着色点p它可能会自发光，所以有一个Le项，表示该点向wo方向发出的radiance
还有一部分能量是反射而来的，反射而来的这部分能量:我们知道brdf是一个入射方向和一个出射方向，那么我们就对这个进行积分，计算每个入射方向对当前出射方向反射的irradiance
dL出 = fr * dE = fr * (dL * cos * dwi)
```

#### （2）光源类型

**一个点光源**：照射物体p只有一条光路
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$


**多个点光源**：就是多条光路，求和
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\sum L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$


**面光源**：积分面光源对应的立体角
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\int L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$
**“光源”有可能是场景中的物体**：多次弹射
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\int L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
\\ L_i:光源、场景中物体(递归计算L_o)
$$
抽象简化成：

「🤔️这里左右两边L看上去不一样，但它是矩阵级数收敛的结果，这里不细研究了～」

E：自放光 KE：一次反射 K^2E：两次反射
$$
l(u)=e(u)+\int l(v)K(u,v)dv
\\ L=E+KL
\\ L = (1-K)^{-1}E
\\ L = (I+K+K^2+K^3+...)E
\\ L=E+KE+K^2E+K^3E+...
$$

### 3.shadow



### 4.环境光照

#### （0）数学前提

<font color='red'>**🌟积分的近似**</font>：
$$
\int_\Omega f(x) g(x)dx\approx \frac{\int_{\Omega_G}f(x)dx}{\int_{\Omega_G}dx}\cdot \int_\Omega g(x)dx
$$
什么时候取等：f(x)是常值函数，或者叫常数

什么时候取约等：（这里f和g是对称的）

- case 1：f/g函数的积分域足够小（support很小）
- case 2：f/g函数足够光滑（也就是近似于常数，波动不大）

#### （1）IBL

环境光照的主流方式：spherical map & cube map，存储在球面上或者立方体上

**IBL：基于图像的照明「图像就是指spherical map 和 cube map」**

分析渲染方程：<font color='green'>**IBL不考虑遮挡**</font>，所以Visibility项可以舍去
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{H^2}L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$
「实时渲染没办法像离线渲染那样去进行蒙特卡洛追踪，对于求积分来说也是很困难的，我们需要尽量简化渲染方程」

两种特殊的材质：

- diffuse：它会反射到各个方向，各个方向的反射强度应该差不多，所以说它很smooth，brdf接近于常数
- glossy：它会集中反射到某些立体角区间，这个区间往往特别小

#### 

























----

#### 球面坐标系

三个参数定义：半径（r），极角（θ），方位角（φ）

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202308282148620.jpeg" alt="ori_56839a2b081d9" style="zoom: 67%;" />

#### 混合偏导数

$$
\frac{\partial^2z}{\partial x\partial y}=f''_{xy}(x,y)=\frac{\partial}{\partial y}(\frac{\partial f}{\partial x})
\\ \neq \frac{\partial z}{\partial x}\cdot \frac{\partial z}{\partial y}
$$

继续推导：
$$
\frac{\partial^2z}{\partial x\partial y}=\frac{\partial}{\partial y}(\frac{\partial f}{\partial x})
\\ 假设:L=\frac{\partial^2z}{\partial x\partial y},E=\frac{\partial f}{\partial x}
\\ 那么: L=\frac{\partial}{\partial y}(E)=\frac{\partial E}{\partial y}
$$

#### Solid Angles

立体角是角度在三维空间的延伸

- 角(弧度制)：弧长 / 半径
- 立体角：投影到球面上的面积 / 半径的平方

🤔️记忆：可以这么记忆，对于角度来说，可以把l投影到r边上，所以是l/r；而立体角来说，是将A投影到圆心的平面上，所以是A/r<sup>2</sup>【当然这肯定是不准确的，只是方便记忆】

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202307311656896.png" alt="截屏2023-07-31 16.55.44" style="zoom:40%;" />

立体角 - 微积分相关：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202307311743333.png" alt="截屏2023-07-31 17.41.06" style="zoom:50%;" />

分析：该微分面积可以看成一个长方形，分别是θ和φ的方向；因为弧长=半径*角度，所以θ方向的长度为rdθ；而φ方向要注意，它投影到底面一定长度小于半径r，所以我们需要找到它的对应半径，其实我们作辅助线，在上面构造一个和底面平行的圆，这个圆的半径是rsinθ，故得证
