#include <iostream>
#include <algorithm>
using namespace std;
struct nod
{
    int val,hLeft,hRight;
    nod *st,*dr;
};
void inssert(nod *&arb, int x,nod *&r,int &h,int h2)
{
    int dif;
    if (arb)
    {
        h++;
        if (arb->val>x)
        {
            inssert(arb->st,x,r,h,h2+1);
            arb->hLeft=h-h2;
        }
        else
        {
            inssert(arb->dr,x,r,h,h2+1);
            arb->hRight=h-h2;
        }
        dif=arb->hLeft-arb->hRight;
        if ( dif<-1 || 1<dif )
            if (!r) r=arb;
    }
    else
    {
        arb=new nod;
        arb->st=arb->dr=NULL;
        arb->hLeft=arb->hRight=0;
        arb->val=x;
    }
}
void echilibreaza(nod *&arb,nod *&r)
{
    int dif=r->hLeft-r->hRight;
    nod *p,*q,*b,*c,*d;
    if(arb)
    {
        if (arb->val==r->val)
        {
            if (dif==2)
            {
                p=r->st;
                dif=p->hLeft-p->hRight;
                if (dif==1)
                {
                    //R
                    q=p->st;
                    c=p->dr;
                    p->st=q;p->dr=r;
                    r->st=c;
                    if (c) r->hLeft=1+max(c->hLeft,c->hRight);
                    else r->hLeft=0;
                    p->hLeft=1+max(q->hLeft,q->hRight);
                    p->hRight=1+max(r->hLeft,r->hRight);
                    r=p;
                }
                else
                {
                    //LR
                    q=p->dr;
                    c=q->st;d=q->dr;
                    p->dr=c;r->st=d;
                    q->st=p;q->dr=r;
                    if (d) r->hLeft=1+max(d->hLeft,d->hRight);
                    else r->hLeft=0;
                    if (c) p->hRight=1+max(c->hLeft,c->hRight);
                    else p->hRight=0;
                    q->hLeft=1+max(p->hLeft,p->hRight);
                    q->hRight=1+max(r->hLeft,r->hRight);
                    r=q;
                }
                arb=r;
            }
            else
                if(dif==-2)
                {
                    p=r->dr;
                    dif=p->hLeft-p->hRight;
                    if (dif==-1)
                    {
                        //L
                        q=p->dr;
                        b=p->st;
                        p->st=r;p->dr=q;
                        r->dr=b;
                        if (b) r->hRight=1+max(b->hLeft,b->hRight);
                        else r->hRight=0;
                        p->hLeft=1+max(r->hLeft,r->hRight);
                        p->hRight=1+max(q->hLeft,q->hRight);
                        r=p;
                    }
                    else
                    {
                        //RL
                        q=p->st;
                        c=q->st;d=q->dr;
                        q->st=r;q->dr=p;
                        r->dr=c;p->st=d;
                        if (d) p->hLeft=1+max(d->hLeft,d->hRight);
                        else p->hLeft=0;
                        if (c) r->hRight=1+max(c->hLeft,c->hRight);
                        else r->hRight=0;
                        q->hLeft=1+max(r->hLeft,r->hRight);
                        q->hRight=1+max(p->hLeft,p->hRight);
                        r=q;
                    }
                    arb=r;
                }
        }
        else
        {
            echilibreaza(arb->st,r);
            echilibreaza(arb->dr,r);
            p=arb->st;
            if (p) arb->hLeft=1+max(p->hLeft,p->hRight);
            else arb->hLeft=0;
            p=arb->dr;
            if (p) arb->hRight=1+max(p->hLeft,p->hRight);
            else arb->hRight=0;
        }
    }

}
void stergeInterior(nod *&arb,nod *&r,nod*&rr)
{
        nod *p;
        if (r->dr)
        {
            stergeInterior(arb,r->dr,rr);
            r->hRight--;
            int dif=r->hLeft-r->hRight;
            if ( dif<-1 || dif>1 )
                rr=arb;
        }
        else
        {
            int aux1=arb->hLeft,aux2=arb->hRight;
            swap(arb->val,r->val);
            p=r->st;
            delete r;
            r=p;
            if (r)
            {
                r->hLeft=aux1-1;
                r->hRight=aux2;
            }
        }

}
void delette(nod *&arb, int x,nod *&r)
{
    nod *p;
    if (arb->val==x)
    {
        if ( arb->st==NULL && arb->dr==NULL )
        {
            //frunza;
            delete arb;
            arb=NULL;
        }
        else
            if (arb->st==NULL)
            {
                //are fiu doar in dreapta
                p=arb->dr;
                delete arb;
                arb=p;
            }
            else
                if (arb->dr==NULL)
                {
                    //are fiu doar in stanga
                    p=arb->st;
                    delete arb;
                    arb=p;
                }
                else stergeInterior(arb,arb->st,r);

    }
    else
    {
        if (arb->val>x)
        {
            delette(arb->st,x,r);
            arb->hLeft--;
        }
        else
        {
            delette(arb->dr,x,r);
            arb->hRight--;
        }
        int dif=arb->hLeft-arb->hRight;
        if ( dif<-1 || dif>1 )
            r=arb;
    }
}
void srd(nod *arb)
{
    if (arb)
    {
        srd(arb->st);
        cout<<arb->val<<' ';
        srd(arb->dr);
    }
}
void rsd(nod *arb)
{
    if (arb)
    {
        cout<<arb->val<<' ';
        rsd(arb->st);
        rsd(arb->dr);
    }
}
int main()
{
    nod *arb=NULL,*r=NULL;
    int x,h,ok=1;
    cout<<"Alegeti doar numele optiunii\n";
    do
    {
        cout<<"1.Insereaza un numar\n2.Sterge un numar\n3.Afiseaza arborele in RSD\n4.Afiseaza arborele in SRD\n5.Exit\n";
        cin>>x;
        switch(x)
        {
        case 1:
            cout<<"Introduceti numarul ";
            cin>>x;
            h=0;
            inssert(arb,x,r,h,0);
            if (r)
                echilibreaza(arb,r);
            r=NULL;
            break;
        case 2:
            cout<<"Introduceti numarul ";
            cin>>x;
            delette(arb,x,r);
            if (r)
                echilibreaza(arb,r);
            r=NULL;
            break;
        case 3:
            rsd(arb);cout<<'\n';
            break;
        case 4:
            srd(arb);cout<<'\n';
            break;
        default:
            ok=0;
            break;
        }
    }
    while(ok);
    return 0;
}
