typedef   struct   Capoint         
{ 
	int   x; 
	int   y; 
}CAPoint; 



//返回向量叉乘，公共点为Po3 
int   VecMultiply(CAPoint   po1,   CAPoint   po2,   CAPoint   po3) 
{ 
        return   (   (   po1.x   -   po3.x   )   *   (   po2.y   -po3.y   )   -   (   po2.x   -   po3.x   )   *   (   po1.y   -   po3.y   )   );         
} 

//判断三点是否共线函数 
bool   PoOnSameLine(CAPoint   po1,CAPoint   po2,CAPoint   po3) 
{ 
	return   (VecMultiply(po1,   po2   ,   po3   )==   0   );   
} 

//判断点p是否是三角形内   p1,p2,p3为三角形的三个顶点 (不包含顶点和边)
bool   PoInTrigon(CAPoint   p1,   CAPoint   p2,   CAPoint   p3,   CAPoint   p) 
{ 
	int   re1   =   VecMultiply(p1,   p   ,   p2); 
	int   re2   =   VecMultiply(p2,   p   ,   p3);   
	int   re3   =   VecMultiply(p3,   p   ,   p1);   
	if   (re1   *   re2   *   re3   ==   0   )   return   false; 
	if   ((re1   > 0   &&   re2   >   0   &&   re3   >   0   )   || 
		(re1   <0   &&   re2   <   0   &&   re3   <   0   )) 
		return   true; 
	return   false; 
} 

//判断点p是否是三角形内   p1,p2,p3为三角形的三个顶点 (包含顶点和边)
int min(int a,int b)
{
    return a<b?a:b;
}


int max(int a,int b)
{
    return a>b?a:b;
}

bool   PoInTrigon(CAPoint   p1,   CAPoint   p2,   CAPoint   p3,   CAPoint   p)
{
    int   re1   =   VecMultiply(p1,   p   ,   p2);
    int   re2   =   VecMultiply(p2,   p   ,   p3);
    int   re3   =   VecMultiply(p3,   p   ,   p1);
    if   ((re1   ==  0) &&  (p.x>=min(p1.x,p2.x))    &&  (p.x<=max(p1.x,p2.x))  &&  (p.y>=min(p1.y,p2.y))  &&  (p.y<=max(p1.y,p2.y)))
            return true;
    if   ((re2   ==  0) &&  (p.x>=min(p3.x,p2.x))    &&  (p.x<=max(p3.x,p2.x))  &&  (p.y>=min(p3.y,p2.y))  &&  (p.y<=max(p3.y,p2.y)))
            return true;
    if   ((re3   ==  0) &&  (p.x>=min(p1.x,p3.x))    &&  (p.x<=max(p1.x,p3.x))  &&  (p.y>=min(p1.y,p3.y))  &&  (p.y<=max(p1.y,p3.y)))
            return true;
    if   ((re1   > 0   &&   re2   >   0   &&   re3   >   0   )   ||
        (re1   <0   &&   re2   <   0   &&   re3   <   0   ))
            return   true;

    return   false;
}