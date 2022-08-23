# Python and Vectorization
## Difference between non vectorized and vectorized version

Vectorization includes use of Numpy library built in functions which make the code run faster.
The non vectorized version includes use of for loop for working on matrices.

An example of that would be multiplying matrix A by a number v.

Non-Vectorized version

Ui = ΣAijvj

U = np.zeros(n,1)

for i ....

for j ...

U[i]=A[i][j]*v[j]

Vectorized version

U=np.dot(A,v)

The vectorized version is almost 300 times faster than than the non vectorized version. This makes a huge difference when working on big data sets.

GPU and CPU are known as SIMD (Single Instruction Multiple Data). When using built in functions, these have a much better advantage of parallelism to do the computation much faster. 
Scalable deep learning implementations are done on GPU.

We should always check if theres a built in function for the operation we are trying to do using a for loop as the computation is much more faster.

Example of in built functions:
np.log (u), np.abs (u), np.maximum (n,0)

## Vectorizing logistic regression

z^(1) = w^Tx^(1) + b, a^(1) = σ(z^(1))

z^(2) = w^Tx^(2) + b, a^(2) = σ(z^(2))

z^(3) = w^Tx^(3) + b, a^(3) = σ(z^(3))

a is the prediction of the output.

Z=[ z^(1) z^(2) z^(3) ....z^(m)] = w^T X^T [bbb .....b], The matrix of b has 1 row and m columns (1xm).

 =[w^Tx^(1) + b w^Tx^(2) + b .... w^Tx^(m) + b]
 
 A=[a^(1) a^(2) .... a^(m)] = σ(Z)
 
 Numpy command:
 
 Z = np.dot(w.T,X) + b
 
 b is a real number. When the code is implemented, b is expanded out to a 1xm row vector. This is called broadcasting.
 
 ## Vectorizing Logistic Regression's Gradient Output
 
 dz^(1)=a^(1)-y^(1),  dz^(2)=a^(2)-y^(2), ......
 
 dZ=[dz^(1) dz^(2) dz^(3) ..... dz^(m)]
 
 A=[a^(1) a^(2) a^(3) ...... a^(m)], Y=[y^(1) y^(2) y^(3) ...... y^(m)]
 
 dZ=A-Y= [(a^(1)-y^(1)) (a^(2)-y^(2)) (a^(3)-y^(3)) ....... (a^(m)-y^(m))]
 
 dw=1/m(XdZ^T)
 
 db=1/m(Σdz^(i))
 
 w = w -	αdw
 
 b = b - 	αdb
 
 For multiple iteration of gradient descent, we might have to use a for loop.
 
 ## Broadcasting in Python
 
 Broadcasting is a technique which helps the code run faster.
 
 Example: If I have a 3x4 matrix A and I want to sum up the columns and then divide the matrix by the sum of the column, the following code can be used.
 
 cal=A.sum(axis=0)
 
 percentage=100*A/(cal.reshape(1,4))
 
 axis=0 is used to sum up the matrix members vertically and axis=1 is used to sum up the matrix members horizontally.
 
Another example would be if we want to add a mxn matrix to a 1xn matrix, the rows of the 1xn matrix are copied to form a mxn matrix and the two are added.
Similarly, if we want to add a mxn matrix to a mx1 matrix, the colums of the mx1 matrix are copied to form a mxn matrix and the two are added.
If a real number is added to a matrix, a matrix of the same order is created where the members are the given real number and the two are added.

### Errors
Broadcasting is very useful but might cause some errors. If we use the following function

a=np.random.randn(5)

a rank 1 array is formed which might not give the expected result.

Instead, a vector should be created. If a rank 1 array is created, it can be reshaped into a row or column vector.

a=np.random.randn(5,1)

a=np.random.randn(1,5)

assert(a.shape == (5,1))






