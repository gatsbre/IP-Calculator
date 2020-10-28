#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
using namespace std;

char ip[20];

void afisareBinar(bool vector[],char s[])
{
	cout << s;
	for(int i = 32; i >= 1; i--)
		{
			if(i%4 == 0 && i%8 != 0)
				cout << ".";
			else if(i%8 == 0 && i!= 32)
				cout << "/";
			cout << vector[i];
		}
	cout << endl;

}

void afisareDecimal(bool vector[],char s[])
{
	cout << s;
	for(int i = 3; i >= 0; i--)
	{		
		int valoare = 0;
		for(int j = 7; j >= 0; j--)
				valoare +=vector[i*8+j+1]<<j;
		cout << valoare;
		if(i != 0)
			cout << ".";
	}
	cout << endl;
}

void ipCalculator(char ip[], unsigned int masca)
{
	bool vector_ip[33],vector_masca[33];
	char *p;

	//TRANSFORMAREA IP-ULUI IN BINAR
	p=strtok(ip,".");
	for(int i = 3; i >= 0; i--)
	{
		int val = atoi(p);

		for(int j = 7; j >= 0; j--)
		{
			if(val >= 1<<j)
				{
					val-=1<<j;
					vector_ip[i*8+j+1]=1;
				}
			else vector_ip[i*8+j+1]=0;
		}
		p=strtok(NULL,".");
	}

	//TRANSFORMAREA MASTII IN BINAR
	int c_masca=masca;
	for(int i = 32; i >= 1; i--)
		if(c_masca)
			{
				vector_masca[i] = 1;
				c_masca--;
			}
		else
			vector_masca[i] = 0;

	//CALCULAREA NETWORK ADDRESS IN BINAR
	bool vector_netAddress[33];
	for(int i = 32; i >= 1; i--)
		vector_netAddress[i] = vector_masca[i] && vector_ip[i];

	//CALCULAREA BROADCAST ADDRESS IN BINAR
	bool vector_broadcast[33];
	for(int i = 1 ; i <= 32; i++)
		vector_broadcast[i]= !vector_masca[i] || vector_netAddress[i];

	//CALCULAREA RANGE-ULUI
	bool vector_rangemic[33], vector_rangemare[33], ok=true;
	for(int i = 1; i <= 32; i++)
		{
			vector_rangemare[i]=vector_broadcast[i];
			vector_rangemic[i]=vector_netAddress[i];
		}
	//ADUNARE IN BINAR	
	for(int i = 1; i <= 32 && ok; i++)
		if(vector_rangemic[i]==0)
		{
			vector_rangemic[i]=1;
			for(int j = i-1; j >= 1; j--)
				vector_rangemic[j]=0;
			ok = false;
		}
	//SCADERE IN BINAR
	ok = true;
	for(int i = 1; i <= 32 && ok; i++)
		if(vector_rangemare[i]==1)
		{
			vector_rangemare[i]=0;
			for(int j = i-1; j >= 1; j--)
				vector_rangemare[j]=1;
			ok = false;
		}		
	
	//AFISARE
	afisareBinar(vector_ip,			 "[IP BINAR]:        ");
	afisareBinar(vector_masca,		 "[MASCA BINAR]:     ");
	afisareBinar(vector_netAddress,	 "[N.A. BINAR]:      ");
	afisareDecimal(vector_netAddress,"[N.A]:             ");
	afisareDecimal(vector_broadcast, "[B.A]:             ");
	afisareDecimal(vector_rangemic,  "[DGW]:             ");
	afisareDecimal(vector_rangemic,	 "[R.A MINIM]:       ");
	afisareDecimal(vector_rangemare, "[R.A MAXIM]:       ");
	c_masca=(1<<(32-masca))-1;;
	cout <<                          "[HOSTS]:           "<<c_masca<<endl;
	cout <<                          "[SWITCHES]:        ";
	if(float(c_masca)/26>c_masca/26)
		cout << c_masca/26+1;
	else
		cout << c_masca/26;
}

int main()
{
	///IP = 129.197.201.115
	/// MASCA = 22
	
    unsigned int x;
    cout << "[IP]:              ";
    cin >> ip;

    cout << "[MASCA]:           ";
    cin >> x;

    ipCalculator(ip, x);
    return 0;
	
}
