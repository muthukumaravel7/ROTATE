#include<iostream>
#include<math.h>
using namespace std;
const int gh=10,gw=10;

class Rotate{
    public:
    int src[gh][gw],h,w,desth,destw;
    float degree,angleRad,rotate[4];
    Rotate()
    {
        h=gh;w=gw;
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                src[i][j]=1+(i*h)+j;
                cout<<src[i][j]<<"\t";
            }
            cout<<endl<<endl;
        }
        degree=45.0;
        angleRad=degree*3.14159265/180;
        float minX = 0, minY = 0, maxX = 0, maxY = 0;

        rotate[0] = cos(angleRad);
        rotate[1] = sin(angleRad);
        rotate[2] = -sin(angleRad);
        rotate[3] = cos(angleRad);

        float corner[4][2];
        corner[0][0] = (rotate[0] * 0) + (rotate[1] * 0);
        corner[0][1] = (rotate[2] * 0) + (rotate[3] * 0);
        corner[1][0] = (rotate[0] * 0) + rotate[1] * (w-1);
        corner[1][1]= (rotate[2] * 0) + rotate[3] * (w-1);
        corner[2][0] = (rotate[0] * (h-1)) + (rotate[1] * 0);
        corner[2][1] = (rotate[2] * (h-1)) + (rotate[3] * 0);
        corner[3][0] = (rotate[0] * (h-1)) + (rotate[1] * (w-1));
        corner[3][1] = (rotate[2] * (h-1)) + (rotate[3] * (w-1));

        for (int i = 0; i< 4; i++)
        {
            if(corner[i][0] < minX)  minX = corner[i][0];
            if(corner[i][0] > maxX)  maxX = corner[i][0];
            if(corner[i][1] < minY)  minY = corner[i][1] ;
            if(corner[i][1]  > maxY)  maxY = corner[i][1] ;
        }

        desth= ((int)maxX - (int)minX) + 1;
        destw= ((int)maxY - (int)minY) + 1;
        
        Rotate_Host();

    }
    void Rotate_Host()
    {   
        cout<<"OUTPUT"<<endl;
        const int dh=desth,dw=destw;
        int dest[dh][dw];
        for(int i=0;i<dh;i++)
            for(int j=0;j<dw;j++)
            {
                dest[i][j]=0;
            }
        /* Actual Rotation */
        float pointx,pointy;
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                pointx = (rotate[0] * i) + (rotate[1] * j);
                pointy = (rotate[2] * i) + (rotate[3] * j); 
                pointy+=(dw/2);
                /*pointy+=(w%2==0)?(dw/2+1):(dw/2); */
                /*cout<<endl<<(i*h)+j+1<<": x: "<<(int)pointx<<"\t y: "<<(int)pointy<<endl;*/
                if(dest[(int)pointx][(int)pointy]==0)
                    dest[(int)pointx][(int)pointy]=src[i][j];  
                else if((dh>(int)pointx)&&(0<=(int)pointx)&&(dw>(int)pointy)&&(0<=(int)pointy))
                {
                    if((int)pointy+1>0 && (int)pointy+1<dw  && dest[(int)pointx][(int)pointy+1]==0)
                        dest[(int)pointx][(int)pointy+1]=src[i][j];
                    else if((int)pointy-1>0 && (int)pointy-1<dw  && dest[(int)pointx][(int)pointy-1]==0)
                        dest[(int)pointx][(int)pointy-1]=src[i][j];
                    else if((int)pointx-1>0 && (int)pointx-1<dh  && dest[(int)pointx-1][(int)pointy]==0)
                        dest[(int)pointx-1][(int)pointy]=src[i][j];
                    else if((int)pointx+1>0 && (int)pointx+1<dh  && dest[(int)pointx+1][(int)pointy]==0)
                        dest[(int)pointx+1][(int)pointy]=src[i][j];
                }
            }
        }
        for(int i=0;i<dh;i++)
        {
            for(int j=0;j<dw;j++)
            {
                if(dest[i][j]!=0)
                    cout<<dest[i][j]<<"\t";
                else
                    cout<<"\t";
            }
            cout<<endl<<endl;
        }
    }
    
};





int main()
{
    Rotate r;
    return 0;
}