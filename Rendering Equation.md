# Rendering Equation

###### 💡本文的顺序：介绍辐射度量学（为引入渲染方程打下基础）=> 介绍渲染方程 => 通过渲染方程理解常见的图形学算法

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
L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{H^2}L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i V(p,\omega_i) d\omega_i
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

**面光源**：积分面光源对应的立体角「TODO：LTC面光源渲染」
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

### 3.数学前提

#### （0）积分的近似

<font color='red'>**🌟积分的近似**</font>：
$$
\int_\Omega f(x) g(x)dx\approx \frac{\int_{\Omega_G}f(x)dx}{\int_{\Omega_G}dx}\cdot \int_\Omega g(x)dx
$$
什么时候取等：f(x)是常值函数，或者叫常数

什么时候取约等：（这里f和g是对称的）

- case 1：f/g函数的积分域足够小（support很小）
- case 2：f/g函数足够光滑（也就是近似于常数，波动不大）

### 4.shadow

「利用渲染方程来理解shadow的原理」：shadow_map中我们直接将V项提取出来：
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{H^2}L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i V(p, \omega_i)d\omega_i
\\
L_o(p,\omega_o)=L_e(p,\omega_o)+ {\color{Red}\frac{\int_{\Omega^+}V(p,w_i)d\omega_i}{\int_{\Omega^+}d\omega_i}} \int_{H^2}L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
\\ 甚至可以写成:L_o(p,\omega_o)=L_e(p,\omega_o)+ {\color{Red}V(p,\omega_i)}\cdot L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$
shadow_map是一个（点）光源，来判断每个物体是否能被照射，在渲染方程中，这种情况甚至不需要积分

### 5.环境光遮蔽 - AO

#### （1）SSAO - 屏幕空间环境光遮蔽

### 6.环境光照

#### （1）IBL

环境光照的主流方式：spherical map & cube map，存储在球面上或者立方体上

**IBL：基于图像的照明「<font color='purple'>图像就是指spherical map 和 cube map</font>」**

分析渲染方程：<font color='green'>**IBL不考虑遮挡**</font>，所以Visibility项可以舍去
$$
L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{H^2}L_i(p,\omega_i)f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$
「实时渲染没办法像离线渲染那样去进行<u>蒙特卡洛追踪</u>，对于求积分来说也是很困难的，我们需要尽量简化渲染方程」

#### （2）Split Sum

两种特殊的材质：这两种材质都允许通过**拆分积分**来进行近似

- diffuse：它会反射到各个方向，各个方向的反射强度应该差不多，所以说它很smooth，brdf接近于常数
- glossy：它会集中反射到某些立体角区间，这个区间往往特别小，也就是积分域很小

$$
L_o(p,\omega_o)={\color{Red}\frac{\int_{\Omega_{f_r}}L_i(p,w_i)d\omega_i}{\int_{\Omega_{f_r}}d\omega_i}} \int_{H^2}f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i
$$



**Split Sum 1st：**L拆出来：其实就是对某个范围采样L再进行平均，也就是**过滤/模糊**操作 => 我们可以提前将环境光图进行不同程度的模糊

**Split Sum 2nd：**右边brdf也需要积分，得需要预计算

Microfacet BRDF：
$$
f(i,o)=\frac{F(i,h)G(i,o,h)D(h)}{4(n,i)(n,o)}
$$
F：菲涅尔项 -> 石里克近似
$$
R(\theta)=R_0+(1-R_0)(1-cos\theta)^5
\\ R_0=(\frac{n_1-n_2}{n_1+n_2})^2
$$
D：法线分布 -> 比如：Beckmann distribution
$$
D(h)=\frac{e^{-\frac{tan^2\theta_h}{\alpha ^2}}}{\pi \alpha^2cos^4\theta_h}
$$
暂时不考虑G项，我们发现brdf可以抽成三个变量：α、θ<sub>v</sub>、R<sub>0</sub>，三维度的预计算还是太高了，继续降维度 => 通过以下方式，将R<sub>0</sub>拆到积分外面：

「这里的θ<sub>v</sub>是出射方向或者是观察方向于法线的夹角，而不是入射光线，所以这里的θ<sub>v</sub>和积分结尾θ<sub>i</sub>是不同的，在积分过程中θ<sub>i</sub>是不断变化的值」

「写成分数形式其实不太直观：其实就是将F项从fr拆出来，那么fr/F就是剩下的D、G等项」
$$
f_r = \frac{f_r}{F}\cdot(R_0+(1-R_0)(1-cos\theta)^5
\\ = \frac{f_r}{F}\cdot(R_0\cdot (1-(1-cos\theta)^5)+(1-cos\theta)^5)
\\ =R_0\cdot\frac{f_r}{F}(1-(1-cos\theta)^5)+\frac{f_r}{F}(1-cos\theta)^5
$$
带入刚刚拆解渲染方程得到的fr的积分中：
$$
\int_{H^2}f_r(p, w_i\rightarrow w_r)cos\theta_i d\omega_i\approx R_0\int_{\Omega^+}\frac{f_r}{F}(1-(1-cos\theta_i)^5)cos\theta_i d\omega_i 
\\ + \int_{\Omega^+}\frac{f_r}{F}(1-cos\theta_i)^5cos\theta_id\omega_i
\\ 抽象成\approx R_0 \cdot A+B
$$
因此fr的积分只剩下α、θ<sub>v</sub>项，α代表roughness，θ可以直接存储它的余弦值cosθ；我们可以得到“两张”**固定的**二维表格（二维数组/纹理），分别存储A和B的预计算结果，甚至可以用**一张图的两个通道**实现：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309151054573.png" alt="截屏2023-09-15 10.54.24" style="zoom: 33%;" />

最后输入α、θ，查询纹理上的A和B，再结合R<sub>0</sub>，我们就能构造出fr的积分结果

#### （3）shadow under Environment Lighting

「shadow，我们是指物体与光源直接是否存在遮挡关系，如果中间有遮挡物，则光源无法照亮物体，产生阴影；对于IBL的cubemap来说，四面八方都有光源，如果我们去考虑每个方向是否有遮挡关系，那么积分又会多一个维度，所以IBL不能做干脆就不做，不考虑遮挡关系，直接拿cubemap照亮场景」

对于IBL来说，其实相当于一个many light的问题，也就相当于有无数个光源去照亮场景（之前做阴影时我们只考虑一个光源的影响），同时Visibility项也是一个难点，因为场景中有无数个光源，那么该物体与光源之间是否被遮挡，难以将V项从积分中提取出来。

解决方案：

- 使用最具有代表性/最亮的光源生成阴影
- Imperfect shadow map
- Light cuts - 将反射物当成光源，将反射物进行归类当成一个面光源
- RTRT - realtime raytracing
- **Precomputed radiance transfer - PRT**

#### （4）PRT

「PRT能够handle环境光照处理不了阴影的问题」

PRT知识体系：

- 背景知识
  - Frequency and filtering
  - Basis functions
- 实时环境光照/全局光照
  - SH：Spherical Harmonics
  - Prefiltered env. lighting
  - PRT

##### Fourier Transform - 傅立叶变换

> 参考文章：https://blog.csdn.net/wangjiangrong/article/details/114322213

傅立叶级数展开：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309151203340.png" alt="截屏2023-09-15 12.03.04" style="zoom: 33%;" />

『

什么是正交：正交是垂直的拓展概念，正交就是内积为0；我们如何定义函数是否正交，引入正交函数（集），也就是乘积和积分的形式，也就是Product Integral【Product Integral本质是一个点乘】

> 维基百科：https://zh.wikipedia.org/wiki/%E6%AD%A3%E4%BA%A4

**正交函数（集）**：对于两个函数f和g，可以定义如下的内积：
$$
<f,g>_w=\int_a^bf(x)g(x)w(x)dx
$$
这里引入一个非负的权函数w(x)，这个内积叫做w(x)的内积；如果**两个函数带权w(x)正交**：
$$
\int_a^bf(x)g(x)w(x)dx=0
$$
基函数是正交的，可以依次证明：

- （1）任意余弦与余弦正交

- （2）任意正弦与正弦正交

- （3）任意正弦与余弦正交

- > 参考：（全网独家发布）傅里叶级数（一）——正交性与完备性（全网首篇证明完备性）的证明、傅里叶变换的直观解释以及相关结论在广义积分甚至勒贝积分下的若干深入补充讨论 - 数学达人上官正申的文章 - 知乎 https://zhuanlan.zhihu.com/p/472769406

』

低频信息：变化不剧烈的信息；图片的低频信息：就是拿一个线去“扫描”图像，图像信息波动不大，波动平缓，那就是低频信息

频域：在不同频率下观察信号，我们可以**通过傅立叶变化将空间域/时域的函数f(x)转换为频域上的函数F(w)**的

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309151220334.png" alt="截屏2023-09-15 12.20.34" style="zoom:50%;" />

「注意频域的图像：**靠近中间的区域表示低频的系数**，如果一个频域图像的白点集中在中心，说明这个图像低频信息较多；为什么图像会有一条竖线和横线：这是因为我们平铺图像时，图像的最右侧和最左侧相接，上下侧相接，这里频率变化最快」

大概了解一下：通过低通滤波（Low-pass filter）只保留低频信号，其实就是取频域图像的中间圆圈（中间是低频信息）；在时域上做卷积，相当于在频域上做乘积/或者叫过滤，如下图：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309151209991.png" alt="截屏2023-09-15 12.09.28" style="zoom:50%;" />

为什么学习频域：为了理解**product integral**，存在一定的滤波意义

- 两个函数乘起来再求积分（对应相乘加起来），可以理解为卷积或者过滤操作，可以把f(x)和g(x)分别看成两个频谱相乘

- 🤔️我觉得可以这么理解：一个函数可以拆成多个基函数，基函数之间是正交的，那么现在两个函数相乘，相当于基函数对应相乘再求和 => 那么如果一个函数的信息集中在低频，相当于高频的系数接近0，那对应相乘会把另一个函数的高频信息弄丢，这也就是低通滤波的作用

- $$
  \int_\Omega f(x)g(x)dx
  $$

基函数（Basic Function）：比如傅立叶级数展开
$$
f(x)=\sum_i c_i \cdot B_i(x)
$$
**球谐函数**（Spherical Harmonics）：球谐函数是一系列二维的基函数，定义在球面上的 => 二维：球面坐标系的θ、φ（俯仰角和方位角）

```cpp
球谐函数具体怎么写出来要使用勒让德多项式，在课程中更关注球谐应用层面
```

每一行的函数族具有相同的频率；第l行有2l+1个函数，分别标号为-l～l；前n阶有个(n+1)^2函数

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309151639694.png" alt="截屏2023-09-15 16.39.48" style="zoom:50%;" />

最重要的性质：B<sub>i</sub>是第i个球谐基函数，c<sub>i</sub>是其对应的系数，我们能通过对f(x)与某个球谐基函数进行<u>product integral</u>，得到对应的系数 => 这种操作我们叫做<font color='red'>**投影**</font>，<u>将f(x)投影到某个基函数上</u> 
$$
{\color{green} c_i=\int_{\Omega}f(\omega)B_i(\omega)d\omega}
$$
依次计算每阶的系数，我们可以恢复出原函数

```cpp
对于diffuse brdf来说,前三阶球谐已经能大致描述brdf(diffuse);
那么既然只拿前3阶描述brdf,那也就只需要用前3阶来描述光照
```

Games202 Lecture6 - 1:10:00























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
