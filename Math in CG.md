# Math in CG

### 1.Vector

#### （1）vector

函数api：

- GLSL：
  - `vec2`、`vec3`、`vec4`

- HLSL：
  - `float2`、`float3`、`float4`

向量的模：

- 一般在两边各加两条竖线表示
  $$
  ||\vec{v}||
  $$
  

#### （2）dot product

点积，别名：内积、数量积

代数定义：

Vec2：
$$
u=(a,b) \ \ \ \ v=(x,y)
\\u\cdot v=ax+by
$$
Vec3：
$$
u=(a,b,c) \ \ \ \ v=(x,y,z)
\\u\cdot v=ax+by+cz
$$
几何定义：
$$
\vec{u}\cdot \vec{v}=||\vec{u}||\cdot||\vec{v}||\cdot cos\theta
$$
可以求某向量在一个方向上的**投影** -- 注意：点积的几何意义只适用于3维以内，高维只有代数定义

```cpp
二维证明:已知点乘的几何意义,利用三角函数和角公式,cos(θ)=cos(α1-α2)=cosα1·cosα2+sinα1·sinα2=ax+by
```

Wiki百科证明 - 任意n维：
$$
\vec{u}\cdot \vec{u}=||\vec{u}||^2
\\ 令:\vec{c}=\vec{a}-\vec{b}
\\ 向量: \vec{c}\cdot \vec{c}=\vec{a}\cdot \vec{a}+\vec{b}\cdot\vec{b}-2\cdot \vec{a}\cdot\vec{b} 
\\ ⬆️这个不等式的前提:向量的平方是点积【或者理解为点乘自身,然后点乘具有分配律】
\\ 向量的模:||\vec{c}||^2=||\vec{a}^2||+||\vec{b}^2||-2||\vec{a}||\cdot||\vec{b}||\cdot cos\theta
\\ 或者写成:c^2=a^2+b^2-2abcos\theta
\\ \because \vec{c}^2=||\vec{c}||^2
\\ \therefore \vec{a}\cdot \vec{b}=||\vec{a}||\cdot||\vec{b}||\cdot cos\theta
$$
<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306181721572.png" alt="截屏2023-06-18 17.21.03" style="zoom:50%;" />

api函数：

- GLSL：`float dot(vec_n, vec_n);`
- HLSL：`float dot(float_n, float_n);`

拓展：点积可以写成矩阵乘法形式（数学做题中出现）

- 可以将其中一个向量进行转置（取决于将向量视为行矩阵还是列矩阵）
  $$
  a\cdot b=ab^T
  $$
  

#### （3）cross product

代数定义：

Vec3：
$$
u=(a,b,c) \ \ \ \ v=(x,y,z)
\\u\times v=(bz-cy,cx-az,ay-bx)
$$
<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306182145753.png" alt="截屏2023-06-18 21.45.18" style="zoom:50%;" />

PS：叉乘可以写成行列式，但其中一行是向量而不是常数，所以叉乘的结果是向量，而不是一个数

几何定义：

- 叉乘结果是一个**向量**，该向量正交于执行叉乘的两个向量

  - ```cpp
    证明:正交就是两分量夹角为90度,那么可以通过点乘进行证明
    ```

- 叉乘的行列式：刚好是以uv为邻边的平行四边形的面积

$$
||u\times v||=||u||\cdot||v||\cdot sin\theta
$$

"Vec2"：

###### <font color='green'>二维有叉乘吗？</font>严格意义来讲，没有。叉乘的定义：两个向量叉乘结果是一个与该两个向量正交的向量，因此在二维空间中，不存在这种向量，不具有几何意义。

$$
u=(a,b) \ \ \ \ v=(x,y)
\\u\times v=(ay-bx)
$$

但我们仍然可以进行这种计算，因为计算的结果是有意义的，(ay-bx)确实能够代表u和v之间的夹角θ的sin值

```cpp
证明:已知点乘的几何意义,利用三角函数和角公式,sin(θ)=sin(α1-α2)=sinα1·cosα2-cosα1·sinα2=ay-bx
```

api函数：

- GLSL：`vec3 cross(vec3, vec3);`

  - ⚠️GLSL的cross函数只支持vec3的叉积操作

  - 为支持vec2叉积，我们可以这么写：

  - ```glsl
    float res = cross(vec3(uv1, 0.0), vec3(uv2, 0.0)).z;
    ```

- HLSL：`float3 cross(float3, float3);` -- *好像支持float2? whatever~*

```cpp
dot/cross product中涉及交换律/结合律等太简单了,用的时候自己推即可
```

#### （4）其他函数

*：

- GLSL/HLSL：都是逐分量相乘

正交化：

- GLSL：`vec_n normalize(vec_n);`
- HLSL：`float_n normalize(float_n);`

模：

- GLSL：`float length(vec_n);`
- HLSL：`float length(float_n);`

#### ※（5）格拉姆-施密特正交化

格拉姆-施密特正交化的作用：已知向量集{...}，对其正交化处理，得到互相正交的新的向量集

算法步骤：依次加入向量，将当前向量减去该向量对已在正交向量集里向量的投影

#### （6）深入探讨：叉乘、点乘

##### 叉乘

- 叉乘交换顺序，结果变反

  - $$
    A\times B=-B\times A
    $$

  - 容易证明：叉乘可以写成行列式的形式，那么交换AB的顺序相当于交换行列式中两行，那么结果变反

- 特殊向量参与叉乘运算

  - ~~单位向量 -- 没有特殊性~~
    $$
    A\times I=(y-z,z-x,x-y)
    $$

  - 0向量
    $$
    A\times0=0
    $$

  - 同一向量之间
    $$
    A\times A=0
    $$
    易证：行列式两行相等，结果为0

- 向量三重积 <=> <font color="red">**叉乘不满足结合律**</font>

  - $$
    A\times (B\times C)=B(A\cdot C)-C(A\cdot B)
    \\ \neq (A\times B)\times C
    $$

  - 向量叉乘为什么不满足交换律：

    - TODO，叉乘的结果的模相同吗？

  - 向量三重积多种证明方式：

    - 推导1：向量运算推导

      `B×C`得到垂直于BOC平面的向量(假设为D)，所以说与T垂直的向量一定在BOC平面中，那么任意向量与D叉乘的结果(假设为K)，首先一定是垂直于D的，那么K一定在BOC平面内，那么得到公式
      $$
      A\times (B\times C)=mB+nC \ \ \ \ (m,n\in R)
      $$
      我们对等式两边同时点乘A：
      $$
      A\cdot (A\times D)=A\cdot (mB+nC)
      \\ A\cdot (A\times D):标量三重积,因两分量相同,所以值为0
      \\ mA\cdot B+nA\cdot C=0
      $$
      假设：
      $$
      m=pA\cdot C \ \ \ \ n=-pA\cdot B \ \ \ \ p\in R
      \\ \therefore A\times (B\times C)=p(A\cdot C)B-p(A\cdot B)C
      $$
      这种假设刚好使等式成立，所以说恒等式中未知数只剩p，我们可以带入特殊向量求p的值

      带入不互相正交的向量，比如：
      $$
      A=(1,1,0) \ \ \ \ B=(1,0,0) \ \ \ \ C=(0,0,1)
      $$
      => 推导出`p=1`，所以推导成功

      ```
      这里推导mn与p的关联性时不太严谨,这里将m与n转换为p,其实用到了m/n=-(A`B)/(A`C),这里没有考虑分母为0的情况,所以应该额外单独讨论
      ```

    - 推导2：结合矩阵推导

      - 推导前提：**向量之间的点乘和叉乘，我们都可以转换为矩阵的形式** -- 叉乘不满足结合律，但矩阵乘法满足结合律

        （前提：我们将向量看作是列向量）

        **点乘**：A向量与B向量的点乘 = A的"转置矩阵"与B矩阵的矩阵乘法
        $$
        A\cdot B=A^TB
        $$
        **叉乘**：A向量与B向量的叉乘 = A的"叉乘矩阵"与B矩阵的矩阵乘法

        叉乘矩阵可以通过叉乘实际结果逆推
        $$
        A\times B=A^\times B
        \\ A^\times =\begin{bmatrix}
         0 & -z & y \\
         z & 0 & -x \\
         -y & x & 0
        \end{bmatrix}
        $$
        **标量乘法**：常数a与向量B的乘法 = 常数写成矩阵
        $$
        aB=A^TB
        \ \ \ \  A=\begin{bmatrix}
         a \\
         a \\
         a
        \end{bmatrix}
        $$
        ```cpp
        这里有一个问题：若把常数a直接写成两个矩阵(C·D)的乘法，那么这两个矩阵与B矩阵的运算符是什么？也是矩阵乘法？？？那么是否可以通过结合律为这三个矩阵进行不同的组合
        aB=(C·D)B=?=C(D·B)
        解析：答案是不行 ❌
        常量与向量的乘法是标量乘法，而向量与向量的乘法是点乘，这个不能混为一谈
        ```
        
        - 推导：
          $$
          A\times (B\times C)=B(A\cdot C)-C(A\cdot B)
          \\ A^\times B^\times C=B(A^TC)-C(A^TB)
          \\ 注意:等式右侧是标量乘法,所以不能通过结合律随意组合
          \\ (A^\times B^\times + A^TB)C=B(A^TC)
          $$
          
          左侧C前面的系数我们可以计算出来：
          $$
          A^\times B^\times=
          \\ A^TB
          $$
          TODO：这种证明方法有错，待研究🧐
  
- 

- 标量三重积
  - 可以写成矩阵形式 - TODO

### 2.Matrix

#### （1）matrix

函数api：

- GLSL：

  - `mat2`、`mat3`、`mat4` -- 其他：`mat2x3`等...

  - 获取分量方法：`m[0][1]`类似二维矩阵的方式

  - ⚠️<font color='red'>**比较反人类，特别注意**：</font>

    - <font color='green'>**GLSL以<u>列</u>为主序**</font>，这句话有如下影响：

      - `mat2x3`：是2列3行矩阵

      - 分量获取也是按照先列后行，`m[0][1]`：第0列第1行

      - 矩阵构造时也是按行构造：

        - 举例：二维旋转矩阵M
          $$
          M=\begin{bmatrix}
          cos\theta  & -sin\theta \\
          sin\theta  & cos\theta
          \end{bmatrix}
          $$

        - 对应glsl代码：`mat2 M = mat2(c, s, -s, c);`

        

- HLSL：

  - `float2x2`、`float3x3`、`float4x4` -- 其他：`float2x3`等..
  - 初始化：矩阵初始化**以行为主序** -- 同Eigen库
  - 同上例：`mat2 M = mat2(c, -s, s, c);`

#### <font color='red'>⚠️（2）vec * mat</font>

向量与矩阵的乘法：

- 首先明确一点：无论是哪种api，左边矩阵提供的都是行，右边矩阵提供的都是列

- 那么为什么会出现**左乘和右乘矩阵的区别**：**是因为不同api对向量的理解不同！**

  - GLSL：**向量被看作列矩阵**，*<u>【🧠这里很好记忆，因为矩阵也是"列"主序，所以其实向量和矩阵的构造函数是相通的】</u>*，所以它只能放在矩阵乘法右侧，所以变化矩阵需要**左乘**

    - 这里有一个容易产生混淆的地方：GLSL是列主序，所以到底是怎么相乘的，举例说明：

      - $$
        M=\begin{pmatrix}
         1 & 3 \\
         2 & 4
        \end{pmatrix}
        $$

      - ```glsl
        // GLSL:
        mat2 m = mat2(1, 2, 3, 4); // 以列主序构造 
        vec2 v = vec2(10, 20);
        vec2 res = m * v; // res:(1*10+3*20, 2*10+4*20)
        
        // 所以可以看出,尽管由列主序构,但并没有说这里的列就等价于了HLSL的行
        ```

    - 变化矩阵综合：`T*R*S`

##### 问题1：左乘或右乘会影响相同变化矩阵的描述吗？如果会影响，当前推导的公式是基于哪种乘法呢，如何对齐左乘与右乘？

比如说我们知道如果一个变化是线性变换，那么它的矩阵表示中每行是对单位基向量做相同的变换，那么这个是基于右乘的前提？

=> 是的，是基于右乘的前提，推导线性变换时，我们是将对应乘法，转换成了矩阵形式：
$$
\tau(\textbf{u})=x\tau(\textbf{i})+y\tau(\textbf{j})+z\tau(\textbf{k})=\begin{bmatrix}
 x & y & z
\end{bmatrix}

{\color{Red}
\begin{bmatrix}
\gets \tau(\textbf{i}) \to  \\
\gets \tau(\textbf{j}) \to \\
\gets \tau(\textbf{k}) \to
\end{bmatrix}
}
$$
所以我们这里其实默认了，坐标或者说向量是以行向量的形式存在，*【因为线性变换的推导是HLSL教材上得来】*

那么我们是否可以得出结论：**如果我们在这里将向量看成列向量，那么左乘的变化矩阵，其实它的每一列是对标准基向量的同等变换！**

所以如何对齐？所以很巧合的是，左乘的api又要求用行向量构造矩阵，所以矩阵初始化时其实连续的片段是有意义的，并没有分隔开；更甚者，我们直接在向量为行向量下推导出矩阵，然后假装自己不知道GLSL是以列为主序这么书写进去，结果是正确的！=> 所以说很多公式或博客其实并没有说明左乘右乘以及api的影响，只是它碰巧就这么对了～

所以我们看到部分博客中旋转矩阵是反的，因为左乘右乘的变化矩阵互相为转置矩阵！！！

> TODO：验证shadertoy旋转：https://www.shadertoy.com/view/DsKSDm

#### （3）matrix multiplication

$$
A_{m*n}*B_{n*p}=C_{m*p}
\\c_{ij}=\sum_k a_{ik}b_{kj}
$$

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202305301847829.jpg" alt="矩阵乘法" style="zoom:15%;" />

###### ⚠️但是大多数api对乘法的定义是完全相反的，这比较annoying！

api函数：【**api往往对矩阵类型"重载"了`*`操作符**】

- GLSL：

  - ❤️<font color='green'>**左乘**</font>：与常规定义相反，*操作符右侧矩阵提供行，左侧矩阵提供列，对应元素相乘 -- 与godot相同【godot底层api是opengl/es】

  - 左乘需要注意的，多个变化矩阵情况：例如SRT矩阵变换

  - ```glsl
    mat3 M = (T * R * S);
    // 或者依次左乘
    M = S * M;
    M = R * M;
    M = T * M;
    ```

- HLSL：

  - <font color='ligblue'>**右乘**</font>：与常规相同


#### （4）transpose

api函数：

- GLSL/HLSL：`transpose`

#### （5）determinant - 行列式

##### 表示方式：

$$
det(A) =|A|
$$
##### 行列式：

- 行列式的定义比较含糊，我们只需要知道，二阶行列式、三阶行列式的公式，以及n阶行列式的递归推导
- n阶行列式：....*{取其中一行，计算`(-1)^(i+j)*对应代数余子式`之和}*

##### 余子式：

- 定义：矩阵去掉第i行第j列后的**行列式** -- 本质上是一个行列式

##### 代数余子式：

- 定义：一个矩阵A的(i,j)代数余子式：C<sub>ij</sub> 是指A的(i,j)余子式M<sub>ij</sub>与(-1)<sup>i+j</sup>的乘积

- $$
  C_{ij}=(-1)^{i+j}M_{ij}
  $$

##### 余子矩阵：

- 定义：A矩阵对应位置存储的是<u>代数余子式</u>

##### 伴随矩阵：

- 记作：adjoint
  $$
  adj(A)=A^*
  $$

- 定义：矩阵A的伴随矩阵是A的余子矩阵C的转置矩阵
  $$
  adj(A)=C^T
  $$

- 应用：

  - 根据拉普拉斯公式的推论，n阶方阵有：
    $$
    AA^*=A^*A=|A|I
    $$

    - 证明：
    - A\*是余子矩阵的转置，这样A和A\*的矩阵乘法中，<u>在对角线</u>上，矩阵元素与对应代数余子式相乘，得到的结果都是det(A)

    $$
    对角线上:\sum_{k=1}^na_{ik}C_{ik}
    $$

    - <u>在非对角线上</u>，相当于将原本第j行元素换成第i行元素求取行列式，<u>**由于有两行相同，所以行列式为0**</u>【或者说：本身正在计算第j行行列式，却把第j行元素替换成了第i行】
      $$
      非对角线上:\sum_{k=1}^na_{ik}C_{jk}
      $$

  - 如果矩阵可逆，可以推导出矩阵的逆和矩阵的伴随之间的关系：
    $$
    AA^*=|A|I
    \\ AA^{-1}=I
    \\ => A^{-1}=\frac{A^*}{|A|}
    $$
    

##### <font color='purple'>行列式的性质</font>：

- 性质1：只要行列式任意一行或列为全0，则行列式为0 - easy
- 性质2：行列式中任意两行(列)互换，行列式的值取反号
- 性质3：如果行列式中某一行所有元素都是两项之和，该行列式可以拆成两个行列式相加
- 性质4：行列式中某一行所有元素都乘以相同的系数k，等价用k乘以此行列式
- 【<font color='green'>**行列式的初等变换**</font>】<font color='red'>**性质5**</font>：行列式某行(列)乘以一个非零常数加到另一行(列)上，行列式不变
  - 推导1：**如果行列式有两行(列)相同，或者成比例，行列式为0** -- 证明：则取其中任意一行乘以-1，加到另一行，使该行元素全部为0

```cpp
性质5的证明:
加到另一行，说明可以把行列式拆分为两个行列式，其中一个为原行列式，另一个行列式中有两行成k倍关系，根据性质2和性质4，所以可以得到这个行列式为0，所以新的行列式等于原行列式
性质5推导1的证明:
可以通过性质5直接证明，或者性质2，两行相同，那么交换两行行列式取反，所以行列式只能为0
```

##### 三阶行列式的快速求法

- 我们可以通过斜对角线快速求的结果：

  - $$
    \begin{vmatrix}
     a & b & c \\
     x & y & z\\
     i & j & k
    \end{vmatrix}=从左到右从上到下-从右到左从上到下=(ayk+bzi+cxj)-(azj+bxk+cyi)
    $$

  - <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202307052332858.png" alt="行列式快速" style="zoom:50%;" />

#### （6）inverse - 逆

##### 定义：

- $$
  AA^{-1}=A^{-1}A=I_n
  $$

##### n阶矩阵A可逆的充要条件：

- $$
  |A|\neq 0
  $$

  

- 其他后续补充...

- 

##### 求法：

- 伴随矩阵法

  - $$
    A^{-1}=\frac{A^*}{|A|}
    $$

- <font color='red'>**初等变化法**</font>

  - 具体步骤：

    - 构造矩阵(A,I)，通过初等变换将A转换为I，我们就得到A<sup>-1</sup>
      $$
      (A,I)\sim(I,A^{-1})
      $$

    - <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306012025542.png" alt="矩阵求逆" style="zoom:50%;" />

  - ###### 参考博客：https://www.sudoedu.com/%E7%BA%BF%E6%80%A7%E4%BB%A3%E6%95%B0%E8%A7%86%E9%A2%91%E8%AF%BE%E7%A8%8B/%E7%9F%A9%E9%98%B5/%E7%94%A8%E5%88%9D%E7%AD%89%E5%8F%98%E6%8D%A2%E6%B1%82%E9%80%86%E7%9F%A9%E9%98%B5/

#### （7）矩阵初等变换

##### 初等变换：

- 交换矩阵的两行
- 以一个非零数k乘矩阵的某一行所有元素
- 把矩阵的某一行所有元素乘以一个不为0的数k，然后加到另一行对应元素

```cpp
其他后续补充:
1.秩
2.特征值
3.Ax=b
......
```

### 3.变换

##### 线性变换：

- 定义：线性变换是一种函数，我们关注输入和输出为三维向量的情况：
  $$
  \tau(\textbf{u})=\tau(x,y,z)=(x',y',z')
  $$
  线性变化需要满足两个性质：
  $$
  \tau(\textbf{u}+\textbf{v})=\tau(\textbf{u})+\tau(\textbf{v})
  \\ \tau(k\textbf{u})=k\tau(\textbf{u})
  $$

- <font color='red'>**线性变换的矩阵表示法**</font>：根据线性变换的性质，我们有意将向量u拆成：
  $$
  \textbf{u}=x\textbf{i}+y\textbf{j}+z\textbf{k}
  \\ 其中:x,y,z是常数,也就是3d坐标;
  \\ \textbf{i} = (1,0,0)\ \ \ \textbf{j}=(0,1,0) \ \ \  \textbf{k}=(0,0,1)
  $$
  那么根据线性变换的性质：
  $$
  \tau(\textbf{u})=τ(x\textbf{i}+y\textbf{j}+z\textbf{k})=x\tau(\textbf{i})+y\tau(\textbf{j})+z\tau(\textbf{k})
  $$
  这种三个对应相乘的形式，我们可以用**向量/矩阵的乘法**表示：
  $$
  \tau(\textbf{u})=\textbf{u}A=\begin{bmatrix}
   x & y & z
  \end{bmatrix}
  
  {\color{Red}
  \begin{bmatrix}
  \gets \tau(\textbf{i}) \to  \\
  \gets \tau(\textbf{j}) \to \\
  \gets \tau(\textbf{k}) \to
  \end{bmatrix}
  }
  $$
  <font color='red'>**我们称矩阵A为线性变化τ的矩阵表示法**</font> => 换言之，**对三维向量的线性变化，都可以转换为矩阵的形式**；<u>特别的，这个矩阵很特殊，矩阵的每行分别是对标准基向量的变换</u> 

  *※<font color='ligblue'>**甚至我们只需要关注对标准基向量的变换!!!**</font>比如当我们关注旋转变换时，(<u>当然我们需要保证它是一个线性变换</u>)，我们只需要关注比如(1,0,0)这个向量在旋转后结果(?,?,?)即可，那比如绕z轴旋转θ角度，非常容易求得结果为(cosθ,sinθ,0)*

**特殊线性变换**：*【对于特殊的线性变换，我们可以很容易根据上面的推导得到对应矩阵】*

- 缩放

  - 对应线性变换函数：
    $$
    s(x,y,z)=(s_xx,s_yy,s_zz)
    $$

  - 对应矩阵：
    $$
    \tau(\textbf{i})=(s_x,0,0)\  \tau(\textbf{j}),\tau(\textbf{k})同理
    \\=>\begin{bmatrix}
     s_x & 0 & 0 \\
     0 & s_y & 0 \\
     0 & 0 & s_z
    \end{bmatrix}
    $$

- 旋转

  - 旋转有许多种，包括：对x/y/z以及任意轴的旋转

  - 常见旋转矩阵：

    【我们约定：正θ角表示逆时针旋转】我们可以通过旋转是线性变换可以推导出特殊旋转矩阵：

    <img src="/Users/goujiayuan/Downloads/IMG_4747.JPG" alt="IMG_4747" style="zoom: 15%;" /> **TODO**

    其实可以发现，这里xyz轴可以任意替换，也不用关心左右手坐标系 -- 比如关于y轴旋转，那么我们考虑zox平面，那么z行就是`cos sin`，x行就是`-sin cos`，以此来记忆

  - 讨论最简单的一种 -- 关于z轴旋转θ度：
    $$
    r(x,y,z)=(?,?,z)
    $$
    这里`?`还真不好求，我们可以通过上面👆论证的，仅仅考虑对标准基向量的变换，快速得到结果

  - 常规旋转 -- 向量v绕轴n以θ旋转【<font color='green'>**罗德里格旋转公式**</font>】

    - 证明：

    - <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306041508474.jpg" alt="罗德里格" style="zoom:20%;" />

    - 我们将v向量分为平行于n轴的向量和垂直于n轴的向量 -- 因为旋转只影响垂直于n轴的向量 

    - $$
      \vec{v}=\vec{v_\bot}+\vec{v_\parallel}
      $$

    - 我们假设n是单位向量(简化表达)：

    - $$
      \vec{v_\parallel}=(\vec{n}\cdot \vec{v})\cdot \vec{n}
      \\ \vec{v_\bot}=\vec{v}-\vec{v_\parallel}
      $$

    - 上面右图可以发现，我们可以将垂直向量的旋转问题，看成一个(原向量的模,0)向量在以下xoy平面旋转：

    - $$
      x轴:\vec{v_\bot} 
      \\ {\color{red} y轴:\vec{n}\times \vec{v} \ 或 \ \vec{n} \times \vec{v_\bot} }
      $$
      
    - 那么旋转后的向量对x轴和y轴的投影之和就是旋转向量：
    
    - $$
      \vec{v_\bot}'=||\vec{v}_\bot||\cdot cos\theta\cdot \frac{\vec{v_\bot}}{||\vec{v}_\bot||}+||\vec{v}_\bot||\cdot sin\theta\cdot \frac{\vec{n}\times \vec{v}}{||\vec{n}\times\vec{v}||}
      \\ {\color{red} \because |\vec{n}\times \vec{v}|=|\vec{v_\bot}|}
      \\ =\vec{v_\bot}\cdot cos\theta + (\vec{n} \times \vec{v})\cdot sin\theta
      $$
    
    - 所以整合公式：
    
    - $$
      \vec{v}'=\vec{v_\parallel}+\vec{v_\bot}'
      \\ =\vec{v_\parallel}+ \vec{v_\bot} \cdot cos\theta+(\vec{n}\times \vec{v})\cdot sin\theta
      \\ =(\vec{n}\cdot \vec{v})\cdot \vec{n}+(\vec{v}-(\vec{n}\cdot \vec{v})\cdot\vec{n})\cdot cos\theta+(\vec{n}\times \vec{v})\cdot sin\theta
      \\ =(1-cos\theta)\cdot(\vec{n}\cdot \vec{v})\cdot \vec{n}+cos\theta\cdot\vec{v}+(\vec{n}\times \vec{v})\cdot sin\theta
      $$
    
    - 结果：
    
    - $$
      {\color{Red} R_n(v)=proj_n(v)+R_n(v_\bot)}
      \\ {\color{Red} =cos\theta \textbf{v}+(1-cos\theta)(\textbf{n}\cdot \textbf{v})\textbf{n}+sin\theta(\textbf{n}\times \textbf{v})}
      $$
    
    - 证明此变换是线性变换：
    
      - 性质1：
    
        - 叉积满足分配率：
          $$
          n\times (v_1+v_2)=n\times v_1+n\times v_2
          $$
    
        - 点积满足分配率：
          $$
          n\cdot(v_1+v_2)=n\cdot v_1 + n\cdot v_2
          $$
    
      - 性质2：易证，不管点积叉积，都可以将常数提取出来
    
    - 当知道变换是线性变换后，我们可以构造矩阵 -- 对标准基向量变换以快速构造：
      $$
      n=(x,y,z) \ \ \ \ \theta
      \\ R_n=\begin{bmatrix} cos\theta+(1-cos\theta)x^2 & (1-cos\theta)xy+sin\theta z & (1-cos\theta)xz-sin\theta y \\ (1-cos\theta) xy-sin\theta z & cos\theta+(1-cos\theta)y^2 & (1-cos\theta)yz+sin\theta x\\ (1-cos\theta)xz+sin\theta y & (1-cos\theta)yz-sin\theta x & cos\theta+(1-cos\theta)z^2 \end{bmatrix}
      $$

- **平移并不是线性变换**

- ‼️<font color='red'>**重要性质：旋转矩阵的逆等于旋转矩阵的转置**</font>

- 🤔️【思考】线性变换的组合是线性变换吗，model矩阵中SRT的SR是线性变换吗？如何通过model矩阵逆推S、R、T矩阵？

  - 线性变换的复合还是线性变换！

    - 解析：考虑什么叫变换的组合，比如旋转和缩放，这两个变换的组合就是先旋转后再缩放，或用代数形式推理：
      $$
      \tau_2(\tau_1(u+v))=\tau_2(\tau_1(u)+\tau_1(v))=\tau_2(\tau_1(u))+\tau_2(\tau_1(v))
      \\ \tau_2(\tau_1(ku))=k\tau_2(\tau_1(u))
      $$

    - 故：SR的复合矩阵的每行依旧是对标准基向量的变化

  - 仿射变换相较于线性变换的特殊性：可以分离出线性变换部分(SR)与平移部分(T)


##### 正交矩阵：

- 定义：如果AA<sup>T</sup>=I或A<sup>T</sup>A=I，则n阶实矩阵A称为正交矩阵

- 正交矩阵的性质：

  - $$
    A^{-1}=A^T
    $$
  
    

  - **A的各行或各列是单位向量，且两两正交**
  
  - $$
    |A|=1或=-1
    $$
  
    - 证明：
      $$
      |AA^T|=|A||A^T|=|A|^2=1
      $$

```cpp
旋转是正交矩阵的证明:
首先旋转是线性变换，所以旋转对应的矩阵的行向量，分别是对标准基向量的变换，那么对这三个标准基向量ijk同时施加旋转，结果依旧是单位向量，且它们之间是两两正交的
```

##### 仿射变换：

- 定义：仿射变换 = 线性变换 + 平移

- $$
  \alpha(u)=\tau(u)+b=uA+b=\begin{bmatrix}
   x & y & z
  \end{bmatrix}
  
  \begin{bmatrix}
  A_{11} & A_{12} & A_{13}  \\
  A_{21} & A_{22} & A_{23}  \\
  A_{31} & A_{32} & A_{33}  
  \end{bmatrix}+\begin{bmatrix}
   b_x & b_y & b_z
  \end{bmatrix}=\begin{bmatrix}
   x' & y' & z'
  \end{bmatrix}
  $$

- 将3d坐标扩充为齐次坐标后：
  $$
  \begin{bmatrix}
   x & y & z & 1
  \end{bmatrix}
  \begin{bmatrix}
   A_{11} & A_{12} & A_{13} & 0 \\
  A_{21} & A_{22} & A_{23} & 0 \\
  A_{31} & A_{32} & A_{33}  & 0 \\
  b_x & b_y & b_z & 1
  \end{bmatrix}=\begin{bmatrix}
   x' & y' & z' & 1
  \end{bmatrix}
  $$
  

##### 坐标系变换：

- 坐标系中基向量理解：

  - 比如3维空间中(x,y,z)坐标：

  - $$
    (x,y,z)=x\textbf{i}+y\textbf{j}+z\textbf{k}
    \\ \vec{i} = (1,0,0)
    \\ \vec{j} = (0,1,0)
    \\ \vec{k} = (0,0,1) 
    $$

  - 所以其实ijk可以是任何向量，xyz是相对这个坐标系的坐标*（好像是废话～）*

- 坐标系之间变换 

  - 两个坐标系之间的变换，假设坐标系A的xyz轴和原点相对于坐标系B的坐标为uvw和Q，那么从坐标系A到坐标系B的坐标转换矩阵为：
    $$
    \begin{bmatrix}
    \leftarrow u \rightarrow \\
    \leftarrow v \rightarrow \\
    \leftarrow w \rightarrow \\
    \leftarrow Q \rightarrow
    \end{bmatrix}
    $$
    那么从B到A的坐标变换矩阵为该矩阵的逆矩阵，也就是uvw这个3x3局部矩阵的逆和Q取反

  - 🔥**记忆方式**：将坐标从A转换到B，变换矩阵为A相对于B的坐标(xyz和原点) -- 与常规认知相反，下意识会认为应该是B相对于A的坐标
  
    - 比如：local->world的变换矩阵，就是local相对于world的坐标，局部坐标系实际在世界空间中的位置 -- "实际上世界空间是固定的，局部空间是处于世界空间中"


### 4.渲染管线

#### （1）坐标系

$$
local \rightarrow world \rightarrow view \rightarrow ndc
$$

坐标系之间的转换只涉及RT，R：rotation，T：transform，是一个仿射变换，可以看成旋转(线性变换)和平移这两个变化矩阵的组合，所以变化矩阵格式如下：
$$
M=\begin{pmatrix}
\tau(\vec{i}) \\
\tau(\vec{j}) \\
\tau(\vec{k}) \\
Q
\end{pmatrix}
$$
‼️<font color='purple'>**重要性质：因为旋转矩阵是正交矩阵，所以求变换矩阵的逆M<sup>-1</sup>很简单，属于旋转的3x3部分的逆就是转置**</font>
$$
M=\begin{pmatrix}
 u_x & u_y & u_z & 0 \\
 v_x & v_y & v_z & 0 \\
 w_x & w_y & w_z & 0 \\
 Q_x & Q_y & Q_z & 1
\end{pmatrix}
\ \ \ \ M^{-1}=
\begin{pmatrix}
 u_x & v_x & w_x & 0 \\
 u_y & v_y & w_y & 0 \\
 u_z & v_z & w_z & 0 \\
 -Q_x & -Q_y & -Q_z & 1
\end{pmatrix}
$$

##### 坐标系变换矩阵简述

- world - `local -> world`

  - local相对于world的坐标，相当于要将物体放在world空间的什么位置

- view - `world -> view`

  - world相对于camera并不好算，反而camera相对于world很简单，只需要摄像机空间朝向(z)，正上方(y)，就能构建view矩阵的逆矩阵

- projection -  `camera -> ndc`

  - 比如将平截头体透视到投影窗口上【相似三角形】，利用矩阵的闲余元素将z从[n,f]映射到[0,1]

  - <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306212013360.png" alt="投影窗口" style="zoom:40%;" />

  - r：aspect ratio 长宽比【记忆方式：分辨率长在前，宽在后】；α：垂直视仰角，这个角度是两倍与水平面的夹角

  - <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306212013110.png" alt="相似三角形" style="zoom:40%;" />
  
  - 其中投影窗口具体离人眼位置，以及长宽具体值并不重要【我们可以假设高为2，那长就为2r】，因为我们最终会将投影窗口根据纵横比映射到后台缓冲区 => 为了去除投影窗口对纵横比的依赖，我们会做一个额外映射，将x从[-r,r]映射到[-1,1] 【透视除法】
  
  - 总结：
    $$
    camera \overset{相似\triangle}{\rightarrow}  homogeneous \overset{透视\div}{\rightarrow}  ndc
    \\ndc: \left\{\begin{matrix} 
      x\in[-1,1] \\ 
      y\in[-1,1] \\ 
      z\in[0,1]
    \end{matrix}\right.
    $$

##### 🌟projection矩阵推导：

> 参考网站：https://blog.csdn.net/shuaigougou5545/article/details/126324406

不妨假设投影窗口长度为2r，宽度为2，那么投影窗口距离人眼距离为1/tan(α/2)，根据相似三角形可以得到：-- 其中，相似三角形能将x映射到[-r,r]，但要满足ndc则还需要进行额外除以r
$$
y_{ndc}=\frac{y}{z}\cdot\frac{1}{tan\frac{\alpha}{2}}
\\ x_{投影平面}=\frac{x}{z}\cdot \frac{1}{tan\frac{\alpha}{2}} \ \ \ x_{ndc}=x_{投影平面}/r
\\ \therefore x'=\frac{x}{r\cdot tan\frac{\alpha}{2}} \cdot \frac{1}{z} \ \ \ \ y'=\frac{y}{tan\frac{\alpha}{2}}\cdot \frac{1}{z}
$$
```cpp
这里我们可以看到,其实r、alpha、n、f共同决定观察的平截头体,所以我们通过定义投影窗口,相当于定义了我们会将xy限制/投影在某个范围内(投影窗口:x坐标[-r,r],y坐标[-1,1])
```

公式中都出现z，但z导致线性关系破裂（难以通过构造矩阵表达），我们可以在构造矩阵时分别处理线性变换和非线性变换【透视除法】-- 透视除法：我们让矩阵结果w分量保存z值，最后再通过xyz同时除以w实现结果

所以我们初步得到了projection矩阵：
$$
(x,y,z,w)\begin{pmatrix}
 \frac{1}{r\cdot tan\frac{\alpha}{2}} & 0 & ? & 0\\
 0 & \frac{1}{tan\frac{\alpha}{2}} & ? & 0\\
 0 & 0 & ? & 1 \\
 0 & 0 & ? & 0
\end{pmatrix}=(x',y',z',w')
$$
我们发现矩阵中关于z的变换的元素闲余，我们可以利用起来，将z从[n,f]近远平面之间进行线性映射到[0,1]

因为z'与xy无关，所以M<sub>02</sub>和M<sub>12</sub>均为0，假设M<sub>22</sub>为A，M<sub>32</sub>为B，那么有如下关系式：
$$
Az+B=z'
\\ z\in[n,f] \rightarrow z'\in[0,1]
$$

##### 🕳️<font color='red'>这里有大坑：我们之后会进行透视除法，所以这里的并不是一个<u>线性映射</u></font> => 这里我们只能保证我们的构造的函数是<font color='green'>保序函数</font>！！

$$
Az+B=z' \ \ \ \ z_{ndc}=z'/z=A+\frac{B}{z}
\\ A+\frac{B}{n}=0 \ \ \ \ A+\frac{B}{f}=1
\\ \therefore A=\frac{f}{f-n} \ \ \ \ B=\frac{-nf}{f-n}
$$

projection矩阵的完整版：
$$
M_{projection}=\begin{pmatrix}
 \frac{1}{r\cdot tan\frac{\alpha}{2}} & 0 & 0 & 0\\
 0 & \frac{1}{tan\frac{\alpha}{2}} & 0 & 0\\
 0 & 0 & \frac{f}{f-n} & 1 \\
 0 & 0 & \frac{-nf}{f-n} & 0
\end{pmatrix}
$$

### 5.rotation

与旋转相关的数学概念有：旋转矩阵、欧拉角、四元数、轴角。

> 参考文章：https://zhuanlan.zhihu.com/p/45404840

#### （1）欧拉角

> **内旋/外旋**：
>
> - https://blog.csdn.net/xinxiangwangzhi_/article/details/124650910
> - https://blog.csdn.net/weixin_42927959/article/details/89880825

##### 内旋/外旋

- 内旋：绕物体自身的坐标系旋转 -- 欧拉角的默认前提

- 外旋：绕惯性系旋转（轴是固定的，不会动）

###### 前提：矩阵乘法一般不满足交换律，所以旋转并不是简单线性累加

##### Z-Y-X欧拉角

TODO：

#### （2）四元数

##### 复数

$$
z=(a,b)=a+bi
\\ \overline{z}=(a,-b)=a-bi
\\ {\color{Red} 人为定义:\ i^2=-1}
$$

- a为实部，b为虚部，虚部单位i，共轭复数虚部相反

- 复数运算规则：

  - $$
    (a,b)\pm(c,d)=(a+c,b+d)
    \\ (a,b)(c,d)=(a+bi)(c+di)=ac+bdi^2+(ab+cd)i=(ac-bd,ab+cd)
    \\ \frac{(a,b)}{(c,d)}=\frac{(a,b)(-c,d)}{(c,d)(-c,d)}=(\frac{ac+bd}{c^2+d^2},\frac{bc-ad}{c^2+d^2}) \ \ \ \  前提:(c^2+d^2\neq0)
    $$

- **极坐标表示法**：复数运算法则与2D向量相似，我们可以将复数看成2D坐标

  - $$
    z=(a,b)=a+bi=rcos\theta+irsin\theta=(rcos\theta,rsin\theta)
    $$

  - **特殊性质 - 复数乘法**：
    $$
    z_1z_2=(r_1cos\theta_1+ir_1sin\theta_1)(r_2cos\theta_2+ir_2sin\theta_2)
    \\=(r_1r_2(cos\theta_1cos\theta_2-sin\theta_1sin\theta_2),r_1r_2(cos\theta_1sin\theta_2+sin\theta_1cos\theta_2))
    \\=(r_1r_2cos(\theta_1+\theta_2), r_1r_2sin(\theta_1+\theta_2))
    $$
    比较该公式与复数的极坐标表示，如果r<sub>2</sub>=1，也就是z<sub>2</sub>为单位复数，则该乘法的结果其实就是对z<sub>1</sub>复数（向量）进行了一个**旋转操作**

    结论：将复数z<sub>1</sub>（把它视为2D向量）与单位复数z<sub>2</sub>相乘就相当于对z<sub>1</sub>进行旋转操作

##### 四元数代数

$$
\textbf{q}=(u,w)=(q_1,q_2,q_3,q_4)=q_1i+q_2j+q_3k+q_4
\\ \overline{\textbf{q}}=(-u,w)=(-q_1,-q_2,-q_3,q_4)=-q_1i-q_2j-q_3k+q_4
\\ {\color{Red} 人为定义:i^2=j^2=k^2=-1,ijk=-1}
\\ \therefore ij=k,\ ji=-k,\ jk=i,\ kj=-i,\ ki=j,\ ik=-j
$$

- u为虚部，w为实部，(这里我们一般将虚部放在前面,与复数相反,问题不大)

- 运算法则：类似于向量和复数

  - 四元数乘法：
    $$
    pq=r=(r_1,r_2,r_3,r_4)=r_1i+r_2j+r_3k+r_4
    $$
  
    对应相乘，能得到i的有：单含i的，以及j与k相乘 
  
    $$
    含i的:\ \ \ \ p_1i*q_4+p_2j*q_3k+p_3k*q_2j+p_4*q_1i
    $$
    同理得到：
    $$
    r_1=p_1q_4+p_2q_3-p_3q_2+p_4q_1
    \\ r_2=-p_1q_3+p_2q_4+p_3q_1+p_4q_2
    \\ r_3=p_1q_2-p_2q_1+p_3q_4+p_4q_3
    \\ r_4=-p_1q_1-p_2q_2-p_3q_3+p_4q_4
    \\ pq=r=(r_1,r_2,r_3,r_4)=\begin{pmatrix}
    p_4  & -p_3 & p_2 & p_1\\
    p_3  & p_4 & -p_1 & p_2\\
     -p_2 & p_1 & p_4 & p_3\\
     -p_1 & -p_2 & -p_3 & p_4
    \end{pmatrix}
    \begin{pmatrix}
    q_1 \\
    q_2 \\
    q_3 \\
    q_4
    \end{pmatrix}
    $$
    结论：四元数的乘法可以写成类似矩阵乘法的形式
    $$
    pq=\begin{pmatrix}
    q_1 \\
    q_2 \\
    q_3 \\
    q_4
    \end{pmatrix}^T
    \begin{pmatrix}
    p_4  & -p_3 & p_2 & p_1\\
    p_3  & p_4 & -p_1 & p_2\\
     -p_2 & p_1 & p_4 & p_3\\
     -p_1 & -p_2 & -p_3 & p_4
    \end{pmatrix}^T
    $$
    - 四元数与纯实数或乘法单位元`e=(0,0,0,1)`
  
      - $$
        pe=\begin{pmatrix}
        p_4  & -p_3 & p_2 & p_1\\
        p_3  & p_4 & -p_1 & p_2\\
         -p_2 & p_1 & p_4 & p_3\\
         -p_1 & -p_2 & -p_3 & p_4
        \end{pmatrix}\begin{pmatrix}
        0 \\
        0 \\
        0 \\
        1
        \end{pmatrix}=p
        \\ ep=\begin{pmatrix}
        1  & 0 & 0 & 0\\
        0  & 1 & 0 & 0\\
        0 & 0 & 1 & 0\\
        0 & 0 & 0 & 1
        \end{pmatrix}\begin{pmatrix}
        p_1 \\
        p_2 \\
        p_3 \\
        p_4
        \end{pmatrix}=p
        $$
  
    - 四元数连乘
  
      - 两个四元数相乘的结果依然是一个四元数（4D向量/行向量或列向量），所以很明显可以连乘，如何用矩阵形式表示：TODO？？？-- 考虑方向：四元数乘法是否具有结合律
  
  - 四元数乘法另一种形式：
  
    - 四元数乘法可以写成点乘和叉乘的形式 => 数学家可能从这里发现了公式与罗德里格公式的相似之处
  
    - 四元数就是向量，所以点积和叉积和向量的定义相同
  
    - $$
      p=(u,a) \ \ \ \ q=(v,b)
      \\ u\times v=(p_2q_3-p_3q_2,p_3q_1-p_1q_3,p_1q_2-p_2q_1)
      \\ u\cdot v=p_1q_1+p_2q_2+p_3q_3
      $$
  
      我们观察之前计算的结果：
      $$
      r_1=p_1q_4+p_2q_3-p_3q_2+p_4q_1
      \\ r_2=-p_1q_3+p_2q_4+p_3q_1+p_4q_2
      \\ r_3=p_1q_2-p_2q_1+p_3q_4+p_4q_3
      \\ r_4=-p_1q_1-p_2q_2-p_3q_3+p_4q_4
      $$
      推导：
      $$
      r_4=-u\cdot v+ab
      \\ r_1=(u\times v)_x+p_1q_4+p_4q_1
      \\ r_2=(u\times v)_y+p_2q_4+p_4q_2
      \\ r_3=(u\times v)_z+p_3q_4+p_4q_3
      \\ \therefore r_{1/2/3}=(u\times v)_{x/y/z}+(bu)_{x/y/z}+(av)_{x/y/z}
      \\ \therefore r=u\times v+bu+av
      $$
      总结：
      $$
      p=(u,a) \ \ \ \ q=(v,b)
      \\ pq=(u\times v+bu+av,-u\cdot v+ab)
      $$
  

##### 四元数相关性质

- 共轭

  - $$
    q=(u,w)=(q_1,q_2,q_3,q_4)
    \\ q*=\overline{q}=(-u,w)=(-q_1,-q_2,-q_3,q_4)
    $$

- 范数（模）

  - $$
    q=(u,w)=(q_1,q_2,q_3,q_4)
    \\ ||q||=\sqrt{u^2+w^2}=\sqrt{q_1^2+q_2^2+q_3^2+q_4^2}
    $$

  - 单位四元数 => 模为1的四元数

  - 显然：
    $$
    ||q||=||\overline{q}||
    $$

- 共轭、范数重要运算法则

  - 共轭的运算与逆类似：通过pq乘法的代数表示进行推导
    $$
    p=(u,a) \ \ \ \ q=(v,b)
    \\ pq=(u\times v+bu+av,-u\cdot v+ab)
    $$
    得到：
    $$
    (pq)^*=q^*p^*
    \\(p+q)^*=p^*+q^*
    $$

  - 重要性质：

    - $$
      {\color{Red} pp^*=||p||^2}
      \\ (r_1,r_2,r_3=0,所以值为纯实数)
      $$

    - $$
      ||pq||=||p||\cdot ||q||
      $$

      证明：
      $$
      \because ||p||=\sqrt{pp^*}
      \\ \therefore ||pq||=\sqrt{(pq)(pq)^*}
      \\ =\sqrt{p(qq^*)p^*}
      \\ = \sqrt{p||q||^2p^*}
      \\ =||q||\sqrt{pp^*}
      \\=||p||\cdot||q||
      $$

- 逆

  - 定义：
    $$
    qq^{-1}=q^{-1}q=1=(0,0,0,1)
    $$

  - 性质：
    $$
    \because qq^{-1}=1 \ \ \ \ qq^*=||q||^2
    \\ \therefore q^{-1}=\frac{q^*}{||q||^2}
    \\ \therefore 单位四元数的逆=其共轭
    $$

- 极坐标表示

  - 极坐标用ρ、θ构造，我们这里不能将ijk看成三维标准基向量*（虽然看起来有那么回事～）*，θ很难说在三维中的意义是什么

  - 首先考虑单位四元数：
    $$
    q=(u,w)
    \\ ||q||=1 \ \ \rightarrow \ \ u^2+w^2=1^2
    \\ \therefore w^2<1
    $$
    u和w这种平方和为1的状况，我们可以考虑`sin^2+cos^2=1`的结构，因为w是1维度，而u是3维度，为了考虑角度与三角函数值唯一对应的情况，我们应该将w视为cos，那么theta角的范围应该在[0,pi]
    $$
    ||w||=cos\theta \ \ \ \ \theta\in[0,\pi]
    \\ ||u||=sin\theta \ ?
    $$
    分析u，一个3维向量的模是sinθ，那么这个三维向量应该是任意单位向量乘上常数sinθ
    $$
    u=sin\theta\cdot n \ \ \ \ ||n||=1
    $$
    所以：
    $$
    q=(u,w)=(nsin\theta,cos\theta) \ \ \ \ \theta\in[0,\pi]
    \\ ||n||=1
    $$
    意味着，**我们可以将一个三维单位向量n和角度θ存入四元数** => 意义：后面到旋转算子就知道了，目前可以透露的是，n代表的任意旋转轴，θ代表的旋转角度，通过旋转算子用四元数表示旋转操作

    考虑特殊情况：

    - θ不在[0,π]的范围

      - θ在[-π,0]的情况，就是反向旋转，用四元数表示：
        $$
        q'=(nsin(-\theta),cos(-\theta))=(-nsin\theta,cos\theta)=q^*
        $$

      - 绕旋转轴旋转角度，最大就是π，那么超过π的

    - n不是单位向量

##### 四元数旋转算子

- ###### 数学家发现，四元数结构qvq*的结果，刚好是罗德里格旋转算法，因此我们就通过对p进行四元包夹乘法

- 前提：

  - q是单位四元数 - 所以q的逆与共轭等价
  - 我们将纯虚数视为向量或坐标v
  - 旋转算子得到的结果期望也是一个纯虚数（向量/坐标）

- 旋转算子的推导：

  - 四元数的旋转算子：
    $$
    v'=qvq^*=qvq^{-1}
    \\ q=(nsin\theta, cos\theta) \ \ \ \ \theta \in [0,\pi] \ \ \ \ ||n||=1
    $$
  
  - 要用到的公式：
  
  $$
  1.四元数乘法:
  \\ p=(u,a) \ \ \ \ q=(v,b)
  \\ pq=(u\times v+bu+av,-u\cdot v+ab)
  \\ 2.罗德里格旋转公式:
  \\ R_n(v)=proj_n(v)+R_n(v_\bot)
  \\ =cos\theta \textbf{v}+(1-cos\theta)(\textbf{n}\cdot \textbf{v})\textbf{n}+sin\theta(\textbf{n}\times \textbf{v})
  \\ 3.向量三重积公式:
  \\ a\times(b\times c)=b(a\cdot c)-c(a\cdot b)
  $$

  - 三重积：

    - $$
      a\cdot (b\times c)=b\cdot(c\times a)=c\cdot (a\times b)
      $$
  
    - 其中任意两向量相等，三重积结果为0
  
  - 
  
  推导：
  $$
  p=(v,0) \ \ \ \ q=(u,w) \ \ \ \ q^{-1}=q^*=(-u,w)
  \\ qpq^*=(u,w)(v,0)(-u,w)
  \\ =(u\times v+wv,-u\cdot v)(-u,w)
  \\ =(a'',b'')
  \\ a''=-u\times v\times u-wv\times u+(u\cdot v)u+wu\times v+w^2v
  \\ b''=(u\times v)\cdot u+wv\cdot u-wu\cdot v=0
  $$
  `b''=0`是我们预期的结果，对于a‘’来说：
  
  ~~分析`-u×v×u`，其中`u×v`是垂直于uv平面的向量假设为t，假定一个手性，绘制出坐标系，那么`t×u`的结果应该是与v相反，所以说总结果为`-u×v×u=v`  -- 错误的🙅，方向是v的方向，但大小并不是~~ 【可以写成`u×(v×u)`，这样可以代向量三重积的公式】
  $$
  a''=-u\times v\times u-wv\times u+(u\cdot v)u+wu\times v+w^2v
  \\ 这里:p=(v,0) \ \ \ \ q=(nsin\theta,cos\theta)=(u,w) \ \ \ \ 且||n||=1
  \\ \therefore a''=2(u\cdot v)u-(u\cdot u)v+2wu\times v+w^2v
  \\=(cos^2\theta-sin^2\theta)v+2sin^2\theta (n\cdot v)n+2sin\theta cos\theta(n\times v)
  \\ = cos2\theta v+(1-cos2\theta)(n\cdot v)n+sin2\theta(n\times v)
  $$
  
  根据推导我们可以看到旋转算子`qvq*`的结果，就是罗德里格旋转公式的结果，n是旋转轴，但θ是真实旋转角度的一半（也就是说我们想要旋转alpha度，那么θ角就是alpha的一半）
  
  ##### 总结：
  
  ##### <font color='purple'>已知向量v（`v=(v,0)`），绕n轴（n轴是单位向量）旋转θ角度，对应的旋转四元数q（`q=(nsinθ, cosθ)`），那么旋转后的新向量v'（`v'=qvq*`：四元数连乘）</font>

### 6.解析几何 

#### （1）长方形与长方形相交 （长方形可旋转）

##### 判断相交的流程：

1. 判断两个长方形的**边是否有相交** -- 相交=>true；否则=>进入2
2. 判断两个长方形是否**存在包含关系** -- 包含=>true；否则=>false
   - 判断x,y的值域范围存在包含关系 - 这与长方形是否存在包含关系等价


---

### 遗留问题

alpha值的物理证明，为什么比如通过透明物质是通过alpha来计算最终光线的；albedo物理意义，透明物体的albedo和不透明物体的区别

坐标系变换矩阵的一些api

用三个角度的坐标系 - 垂直视仰角

vec与vec相乘，透视乘法？

判断是否有逆

-----

### n.基本数学定理

#### （1）余弦定理

余弦定理定义：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306181730326.png" alt="截屏2023-06-18 17.30.48" style="zoom:50%;" />
$$
cos\alpha=\frac{b^2+c^2-a^2}{2bc}
\\ a^2=b^2+c^2-2bc\cdot cos\alpha
$$
余弦定理证明：

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202306181739507.png" alt="截屏2023-06-18 17.39.29" style="zoom:33%;" />
$$
c=b\cdot cos\alpha+a\cdot cos\beta
\\ c^2=bc\cdot cos\alpha+ac\cdot cos\beta
\\ 同理:a^2=ab\cdot cos\gamma+ac\cdot cos\beta \ \ \ \ b^2=ab\cdot cos\gamma+bc\cdot cos\alpha
\\ \therefore a^2+b^2-c^2=2ab\cdot cos\gamma
$$

----

### 奇怪的知识

- 逆&除法：
  - 当乘法满足交换律时，我们用除法定义；当乘法不满足交换律时，我们用逆定义；



-------

OpenGL与DirectX：

- OpenGL是右手坐标系，DirectX是左手坐标系
  - 摄像机空间中，正上方为y轴，正右方为x轴，那么可以通过左右手来判断，当前api的摄像机正前方是z的正半轴还是负半轴
