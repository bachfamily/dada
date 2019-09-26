/***************************************************************
*  Copyright (C) 2013 Quan Wang <wangq10@rpi.edu> 
*  Signal Analysis and Machine Perception Laboratory 
*  Department of Electrical, Computer, and Systems Engineering 
*  Rensselaer Polytechnic Institute, Troy, NY 12180, USA
* 
*  Related publication: 
*  Quan Wang, Kim L. Boyer. 
*  Feature Learning by Multidimensional Scaling and its Applications in Object Recognition. 
*  2013 26th SIBGRAPI Conference on Graphics, Patterns and Images (Sibgrapi). IEEE, 2013. 
***************************************************************/

#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

#define MAX_LINE_LENGTH 100000
#define EPSILON 0.0000001
namespace smat
{

	/**********************************************
	* Declaration part
	**********************************************/

	template<class T>
	class Matrix
	{
	public:
		Matrix(int rows, int columns); // initialization without assigning values
		Matrix(int rows, int columns, T value); // initialization with all same values
		Matrix(int rows, int columns, std::string type, unsigned random_seed); // special matrix such as I
		Matrix(const char * filename); // load matrix from txt file
		~Matrix(); // destruction
		
		void set(int r, int c, T value); // row, column, value
		T get(int r, int c); // row, column
		int rows(); // number of rows
		int columns(); // number of columns
		
		void print(); // print the matrix
		Matrix * copy(); // copy itself to a new matrix
		
		void saveTxt(const char * filename); // save matrix to txt file
		
		// B=M'
		Matrix * transpose();
		// B=M(r1:r2,c1:c2)
		Matrix * sub(int r1, int r2, int c1, int c2); // submatrix
		// B=|M|
		Matrix * abs(); // absolute values
		
		// numbers of matrix
		T trace(); // trace
		double fnorm(); // Frobenius norm
		double pnorm(double p); // p-norm
		T maxEl(int &r, int &c); // max element
		T minEl(int &r, int &c); // min element
		double mean(); // mean of elements
		T sum(); // sum of elements
		double std(); // standard deviation of elements
		
		
		// M=M+a
		void addNumberSelf(T value); // add a number to itself in space
		// M=M*a
		void multiplyNumberSelf(T value); // add a number to itself in space
		
		// M=M+A
		void addMatrixSelf(Matrix * A); // add a matrix to itself in space
		// M=M.*A
		void dotMultiplyMatrixSelf(Matrix * A); // dot multiply a matrix to itself in space
		
		// B=M+A
		Matrix * addMatrixNew(Matrix * A); // add a matrix to itself with new matrix
		// B=M.*A
		Matrix * dotMultiplyMatrixNew(Matrix * A); // dot multiply a matrix to itself with new matrix
		// B=M*A
		Matrix * multiplyMatrixNew(Matrix * A); // multiply a matrix to itself with new matrix

	private:
		int rows_;
		int columns_;
		T **v;
	};



	/**********************************************
	* Utilities part
	**********************************************/

	template<class T>
	T min(T v1, T v2)
	{
		if(v1<v2) return v1;
		else return v2;
	}
	
	template<class T>
	T max(T v1, T v2)
	{
		if(v1>v2) return v1;
		else return v2;
	}
	
	template<class T>
	void swap(T &v1, T &v2)
	{
		T v3=v1;
		v1=v2;
		v2=v3;
	}
	
	template<class T>
	double sign(T v)
	{
		if(v>0) return 1.0;
		else if(v<0) return -1.0;
		else return 0.0;
	}
	
	/**********************************************
	* Implementation part
	**********************************************/
	
	template<class T>
	Matrix<T>::Matrix(int rows, int columns) // initialization without assigning values
	{
		if(rows<1||columns<1)
		{
			printf("Invalid construction arguments: rows=%d, columns=%d\n",rows,columns);
			exit(1);
		}
		
		rows_=rows;
		columns_=columns;
		
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
		}
	}
	
	template<class T>
	Matrix<T>::Matrix(int rows, int columns, T value) // initialization with all same values
	{
		if(rows<1||columns<1)
		{
			printf("Invalid construction arguments: rows=%d, columns=%d\n",rows,columns);
			exit(1);
		}
		
		rows_=rows;
		columns_=columns;
		
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
			
			for(int j=0;j<columns;j++)
			{
				v[i][j]=value;
			}
		}
	}
	
	template<class T>
	Matrix<T>::Matrix(int rows, int columns, std::string type, unsigned random_seed) // special matrix such as I
	{
		if(rows<1||columns<1)
		{
			printf("Invalid construction arguments: rows=%d, columns=%d\n",rows,columns);
			exit(1);
		}
		rows_=rows;
		columns_=columns;
		
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
		}
		
		if(type.compare("I")==0)
		{
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<columns;j++)
				{
					if(i==j) v[i][j]=(T)1;
					else v[i][j]=(T)0;
				}
			}
		}
		
		else if(type.compare("rand")==0) // all elements between 0 and 1
		{
			srand (random_seed);
			int r1;
			double r2;
			for(int i=0;i<rows_;i++)
			{
				for(int j=0;j<columns_;j++)
				{
					r1=rand()*rand()+rand()*rand()+rand();
					if(r1<0) r1=-r1;
					r2=double(r1%1000001)/1000000;
				
					v[i][j]=(T)r2;
				}
			}
		}
		
		else if(type.compare("rand_int")==0)
		{
			srand (random_seed);
			for(int i=0;i<rows_;i++)
			{
				for(int j=0;j<columns_;j++)
				{
					v[i][j]=(T)rand();
				}
			}
		}
		
		else if(type.compare("randperm")==0) // random permutation, each column is a randperm vector of size rows*1
		{
			srand (random_seed);
			for(int j=0;j<columns;j++)
			{
				for(int i=0;i<rows;i++)
				{
					v[i][j]=i+1;
				}
				
				for(int i=0;i<rows;i++)
				{
					int k=rand()%rows;
					if(k>=rows || k<0)
					{
						printf("Invalid row index: %d\n",k);
						exit(1);
					}
					T temp=v[i][j];
					v[i][j]=v[k][j];
					v[k][j]=temp;
				}
			}
		}
		
		else
		{
			printf("Undefined matrix type: %s\n",type.c_str());
			exit(1);
		}
	}
	
	template<class T>
	Matrix<T>::Matrix(const char * filename)
	{
		FILE * pFile;
		// first pass: matrix size
		int rows=0;
		int columns=0;
		
		pFile=fopen(filename,"r");
		if(pFile==NULL)
		{
			printf("File \"%s\" cannot be found.\n",filename);
			exit(1);
		}
		char line[MAX_LINE_LENGTH];
		char * token=NULL;
		while( fgets (line , MAX_LINE_LENGTH , pFile) != NULL )
		{
			rows++;
			if(rows==1) // count the number of columns
			{
				token=strtok(line," ,\t");
				while(token!=NULL && token[0]>=32)
				{
					columns++;
					token=strtok(NULL," ,\t");
				}
			}
			else // check whether every row contains the same number of elements with the first row
			{
				int check=0;
				token=strtok(line," ,\t");
				while(token!=NULL && token[0]>=32)
				{
					check++;
					token=strtok(NULL," ,\t");
				}
				if(check<columns)
				{
					rows--;
					break;
				}
			}
		}
		fclose (pFile);
		printf("Reading matrix from file \"%s\": %d rows, %d columns\n",filename,rows,columns);
		
		// second pass: read data
		rows_=rows;
		columns_=columns;
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
		}
		
		pFile=fopen(filename,"r");
		if(pFile==NULL)
		{
			printf("File \"%s\" cannot be found.\n",filename);
			exit(1);
		}
		int i=0;
		while( fgets (line , MAX_LINE_LENGTH , pFile) != NULL )
		{
			if(i>=rows) break;
			for(int j=0;j<columns;j++)
			{
				if(j==0) token=strtok(line," ,\t");
				else token=strtok(NULL," ,\t");
				v[i][j]=(T)atof(token);
			}
			i++;
		}
		fclose (pFile);
	}
	
	template<class T>
	Matrix<T>::~Matrix() // destruction
	{
		for(int i=0;i<rows_;i++)
		{
			delete[] (T *)v[i];
		}
		delete[] v;
	}
		
	template<class T>
	void Matrix<T>::set(int r, int c, T value) // row, column, value
	{
		if(r<0 || r>=rows_ || c<0 || c>=columns_)
		{
			printf("Invalid index in set(): r=%d, c=%d\n",r,c);
			exit(1);
		}
		v[r][c]=value;
	}
	
	template<class T>
	T Matrix<T>::get(int r, int c) // row, column
	{
		if(r<0 || r>=rows_ || c<0 || c>=columns_)
		{
			printf("Invalid index in get(): r=%d, c=%d\n",r,c);
			exit(1);
		}
		return v[r][c];
	}
	
	template<class T>
	int Matrix<T>::rows() // number of rows
	{
		return rows_;
	}
	
	template<class T>
	int Matrix<T>::columns() // number of columns
	{
		return columns_;
	}
	
	template<class T>
	void Matrix<T>::print() // print the matrix
	{
		printf("\n");
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				printf("%8.3f    ",(double)v[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::copy() // copy itself to a new matrix
	{
		Matrix<T> * A=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				A->set(i,j,v[i][j]);
			}
		}
		return A;
	}
	
	template<class T>
	void Matrix<T>::saveTxt(const char * filename)
	{
		FILE * pFile;
		pFile=fopen(filename,"w");
		if(pFile==NULL)
		{
			printf("Cannot save to file \"%s\".\n",filename);
			exit(1);
		}
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				fprintf(pFile,"%f  ",(double)v[i][j]);
			}
			fprintf(pFile,"\n");
		}
		fclose(pFile);
		printf("Matrix saved to file \"%s\"\n",filename);
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::transpose()
	{
		Matrix<T> * A=new Matrix<T>(columns_,rows_);
		for(int i=0;i<columns_;i++)
		{
			for(int j=0;j<rows_;j++)
			{
				A->set(i,j,v[j][i]);
			}
		}
		return A;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::sub(int r1, int r2, int c1, int c2) // submatrix
	{
		if(r1<0 || r1>=rows_ || r2<0 || r2>=rows_ || r2<r1 || c1<0 || c1>=columns_ || c2<0 || c2>columns_ || c2<c1)
		{
			printf("Invalid submatrix indices.\n");
			exit(1);
		}
		
		int newRows=r2-r1+1;
		int newColumns=c2-c1+1;
		Matrix<T> * A=new Matrix<T>(newRows,newColumns);
		for(int i=0;i<newRows;i++)
		{
			for(int j=0;j<newColumns;j++)
			{
				A->set(i,j,v[i+r1][j+c1]);
			}
		}
		return A;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::abs() // absolute values
	{
		Matrix<T> * A=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				A->set(i,j,v[i][j]>0?v[i][j]:-v[i][j]);
			}
		}
		return A;
	}
	
	template<class T>
	T Matrix<T>::trace() // trace
	{
		T x=0;
		for(int i=0;i<min<int>(rows_,columns_);i++)
		{
			x+=v[i][i];
		}
		return x;
	}
	
	template<class T>
	double Matrix<T>::fnorm() // Frobenius norm
	{
		double x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+=(v[i][j]*v[i][j]);
			}
		}
		return sqrt(x);
	}
	
	template<class T>
	double Matrix<T>::pnorm(double p) // p-norm
	{
		double x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+= pow(fabs((double)v[i][j]),p);
			}
		}
		return pow(x,1/p);
	}
	
	template<class T>
	T Matrix<T>::maxEl(int &r, int &c) // max element
	{
		T x=v[0][0];
		r=0;
		c=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				if(v[i][j]>x)
				{
					x=v[i][j];
					r=i;
					c=j;
				}
			}
		}
		return x;
	}
	
	template<class T>
	T Matrix<T>::minEl(int &r, int &c) // min element
	{
		T x=v[0][0];
		r=0;
		c=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				if(v[i][j]<x)
				{
					x=v[i][j];
					r=i;
					c=j;
				}
			}
		}
		return x;
	}
	
	template<class T>
	double Matrix<T>::mean() // mean of elements
	{
		double x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+=(double)v[i][j];
			}
		}
		return x/rows_/columns_;
	}
	
	template<class T>
	T Matrix<T>::sum() // sum of elements
	{
		T x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+=v[i][j];
			}
		}
		return x;
	}
	
	template<class T>
	double Matrix<T>::std() // standard deviation of elements
	{
		double m=mean();
		double s=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				s+= (v[i][j]-m)*(v[i][j]-m);
			}
		}
		s=s/rows_/columns_;
		return sqrt(s);
	}
	
	template<class T>
	void Matrix<T>::addNumberSelf(T value) // add a number to itself in space
	{
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]+=value;
			}
		}
	}
	
	template<class T>
	void Matrix<T>::multiplyNumberSelf(T value) // add a number to itself in space
	{
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]*=value;
			}
		}
	}
	
	template<class T>
	void Matrix<T>::addMatrixSelf(Matrix * A) // add a matrix to itself in space
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix summation.\n");
			exit(1);
		}
		
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]+=A->get(i,j);
			}
		}
	}
	
	template<class T>
	void Matrix<T>::dotMultiplyMatrixSelf(Matrix * A) // dot multiply a matrix to itself in space
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix dot multiplication.\n");
			exit(1);
		}
		
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]*=A->get(i,j);
			}
		}
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::addMatrixNew(Matrix * A) // add a matrix to itself with new matrix
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix summation.\n");
			exit(1);
		}
		
		Matrix<T> * B=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				B->set(i,j,v[i][j]+A->get(i,j));
			}
		}
		return B;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::dotMultiplyMatrixNew(Matrix * A) // dot multiply a matrix to itself with new matrix
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix dot multiplication.\n");
			exit(1);
		}
		
		Matrix<T> * B=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				B->set(i,j,v[i][j]*A->get(i,j));
			}
		}
		return B;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::multiplyMatrixNew(Matrix * A) // multiply a matrix to itself with new matrix
	{
		if(columns_!=A->rows())
		{
			printf("Unmatched matrix sizes in matrix multiplication.\n");
			exit(1);
		}
		
		Matrix<T> * B=new Matrix<T>(rows_,A->columns());
		T temp;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<A->columns();j++)
			{
				temp=0;
				for(int k=0;k<columns_;k++)
				{
					temp+= (v[i][k]*A->get(k,j));
				}
				B->set(i,j,temp);
			}
		}
		return B;
	}
	

	/**********************************************
	* Algorithm part
	**********************************************/	
	
	// Calculate the pairwise interpoint Euclidean distances
	// X is data matrix, D is distance matrix
	void EuclideanDistanceMatrix(Matrix<double> * X, Matrix<double> * D)
	{
		int i,j,k;
		double temp;
		if(D==NULL)
		{
			printf("Input matrix pointer is NULL.\n");
			exit(1);
		}
		else if(X->rows()!=D->rows() || X->rows()!=D->columns())
		{
			printf("Invalid distance matrix dimension.\n");
			exit(1);
		}
		
		for(i=0;i<D->rows();i++) D->set(i,i,0.0);
		
		for(i=0;i<D->rows()-1;i++)
		{
			for(j=i+1;j<D->columns();j++)
			{
				temp=0;
				for(k=0;k<X->columns();k++)
				{
					temp+= pow(X->get(i,k)-X->get(j,k),2);
				}
				D->set(i,j,sqrt(temp));
			}
		}
		
		for(i=1;i<D->rows();i++)
		{
			for(j=0;j<i;j++)
			{
				D->set(i,j,D->get(j,i));
			}
		}
	}
	
	// Copy all elements of X to Y
	void ElementCopy(Matrix<double> * X, Matrix<double> * Y)
	{
		if(Y==NULL)
		{
			printf("Input matrix pointer is NULL.\n");
			exit(1);
		}
		else if(X->rows()!=Y->rows() || X->columns()!=Y->columns())
		{
			printf("Invalid matrix dimension.\n");
			exit(1);
		}
		for(int i=0;i<X->rows();i++)
		{
			for(int j=0;j<X->columns();j++)
			{
				Y->set(i,j,X->get(i,j));
			}
		}
	}
	
	// Multidimensional scaling (MDS)
	// This function re-implements Laurens van der Maaten's MDS in his Matlab Toolbox for Dimensionality Reduction
	// The Matlab MDS can be downloaded at http://crcv.ucf.edu/source/dimension
	Matrix<double> * MDS_UCF(Matrix<double> * D, Matrix<double> * X0, int dim, int iter, unsigned random_seed)
	{
		if(D->rows()!=D->columns())
		{
			printf("Input distance matrix to MDS is not square.\n");
			exit(1);
		}
		if(dim<1)
		{
			printf("Invalid dimension for MDS.\n");
			exit(1);
		}
		if(iter<1)
		{
			printf("Invalid number of iterations for MDS.\n");
			exit(1);
		}
		
		Matrix<double> * X=NULL;
		
		// with initialization
		if(X0!=NULL)
		{
			if(X0->rows()!=D->rows() || X0->columns()!=dim)
			{
				printf("Input initialization to MDS has invalid dimension.\n");
				exit(1);
			}
			X=X0->copy();
		}
		// without initialization
		else
		{
			X=new Matrix<double>(D->rows(),dim,"rand", time(NULL));
			double D_mean=D->mean(); // mean value of distance matrix
			X->addNumberSelf(-0.5); // move to the center
			X->multiplyNumberSelf(0.1*D_mean/(1.0/3.0*sqrt((double)dim))); // before this step, mean distance is 1/3*sqrt(d)
		}
		
		double lr=0.05; // learning rate
		double r=2; // metric
		int n=D->rows(); // number of vectors
		
		
		Matrix<double> * dh=new Matrix<double>(n,n,0.0);
		Matrix<double> * pmat=new Matrix<double>(n,dim);
		Matrix<double> * dhdum=new Matrix<double>(n,1);
		Matrix<double> * dhmat=new Matrix<double>(n-1,dim,0);
		
		Matrix<int> * RP=new Matrix<int>(n,iter,"randperm", random_seed); // the matrix for random permutation numbers
		int i,j;
		double temp;
		int m;
		
//		printf("MDS iteration:");
		for(int it=0;it<iter;it++) // iterations
		{
//			if(it%10==0) printf("\n");
//			printf("%3d  ",it+1);
			for(int rp=0;rp<n;rp++) // work on each vector in a randomly permuted order
			{
				m=RP->get(rp,it)-1;
				
				for(i=0;i<n;i++)
				{
					for(j=0;j<dim;j++)
					{
						pmat->set(i,j,  X->get(m,j)-X->get(i,j)  );
					}
				}
				
				for(i=0;i<n;i++)
				{
					temp=0;
					for(j=0;j<dim;j++)
					{
						temp+= pow(fabs(pmat->get(i,j)), r);
					}
					dhdum->set(i,0,  pow(temp,1/r)  );
				}

				for(i=0;i<n;i++)
				{
					if(i==m) continue;
					
					dh->set(m,i,  dhdum->get(i,0)  );
					dh->set(i,m,  dhdum->get(i,0)  );
				}

				for(i=0;i<n-1;i++)
				{
					int ii=i;
					if(i>=m) ii=i+1;
					temp=lr * ( dhdum->get(ii,0)-D->get(ii,m) ) * pow( dhdum->get(ii,0), 1-r );
                    
                    if (temp != temp) {
                        long foo = 8;
                        foo++;
                        temp = 0; // Temporary fix. But dhdum->get(ii,0) can be zero!
                    }

                    
					for(j=0;j<dim;j++)
					{
						dhmat->set(i,j,  temp  );
					}
				}
				
				for(i=0;i<n-1;i++)
				{
					int ii=i;
					if(i>=m) ii=i+1;
					for(j=0;j<dim;j++)
					{
						temp=X->get(ii,j);
						
                        temp+= dhmat->get(i,j) * pow(fabs( pmat->get(ii,j) ),r-1) * sign<double>(pmat->get(ii,j));
						
						X->set(ii,j,temp);
					}
				}
			}
		}
		
//		printf("\n");
		
		delete dh;
		delete pmat;
		delete dhdum;
		delete dhmat;
		delete RP;
		
		return X;
	}
	
	// Multidimensional scaling (MDS) with SMACOF
	// This code re-implements Michael Bronstein's SMACOF in his Matlab Toolbox for Surface Comparison and Analysis
	// The Matlab SMACOF can be downloaded at http://tosca.cs.technion.ac.il/
	Matrix<double> * MDS_SMACOF(Matrix<double> * D, Matrix<double> * X0, int dim, int iter, unsigned random_seed)
	{
		if(D->rows()!=D->columns())
		{
			printf("Input distance matrix to MDS is not square.\n");
			exit(1);
		}
		if(dim<1)
		{
			printf("Invalid dimension for MDS.\n");
			exit(1);
		}
		if(iter<1)
		{
			printf("Invalid number of iterations for MDS.\n");
			exit(1);
		}
		
		Matrix<double> * X=NULL;
		
		// with initialization
		if(X0!=NULL)
		{
			if(X0->rows()!=D->rows() || X0->columns()!=dim)
			{
				printf("Input initialization to MDS has invalid dimension.\n");
				exit(1);
			}
			X=X0->copy();
		}
		// without initialization
		else
		{
			X=new Matrix<double>(D->rows(),dim,"rand", random_seed);
			double D_mean=D->mean(); // mean value of distance matrix
			X->addNumberSelf(-0.5); // move to the center
			X->multiplyNumberSelf(0.1*D_mean/(1.0/3.0*sqrt((double)dim))); // before this step, mean distance is 1/3*sqrt(d)
		}
		
		
		Matrix<double> * Z=X->copy();
		Matrix<double> * D_=new Matrix<double>(D->rows(),D->columns());
		Matrix<double> * B=new Matrix<double>(D->rows(),D->columns());
		int i,j,k;
		double temp;
		
		EuclideanDistanceMatrix(X,D_);

//		printf("MDS iteration:");
		for(int it=0;it<iter;it++) // iterations
		{
//			if(it%10==0) printf("\n");
//			printf("%3d  ",it+1);

			// B = calc_B(D_,D);
			for(i=0;i<D->rows();i++)
			{
				for(j=0;j<D->columns();j++)
				{
					if(i==j || fabs(D_->get(i,j))<EPSILON)
					{
						B->set(i,j,0.0);
					}
					else
					{
						B->set(i,j, -D->get(i,j)/D_->get(i,j) );
					}
				}
			}

			for(j=0;j<D->columns();j++)
			{
				temp=0;
				for(i=0;i<D->rows();i++)
				{
					temp+=B->get(i,j);
				}
				B->set(j,j,-temp);
			}

    		// X = B*Z/size(D,1);
    		for(i=0;i<X->rows();i++)
    		{
    			for(j=0;j<X->columns();j++)
    			{
    				temp=0;
    				for(k=0;k<B->columns();k++)
    				{
    					temp+= ( B->get(i,k)*Z->get(k,j));
    				}
    				X->set(i,j,temp/(double)D->rows());
    			}
    		}
    		
    		// D_ = calc_D (X);
    		EuclideanDistanceMatrix(X,D_);
	
    		// Z = X;
			ElementCopy(X,Z);
		}
    	
//		printf("\n");
		
		delete Z;
		delete D_;
		delete B;
		
		return X;
	}
}

#endif
