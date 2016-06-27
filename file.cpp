#include<iostream>   
#include<string>   
#include<io.h>   
#include<vector>
using namespace std; 

  int   filesearch(string path,int layer,vector<string>& file)   
  {   
          struct _finddata_t   filefind;   
          string  curr=path+"\\*.*";   
          int   done=0,i,handle;   
		  int size=0;
          if((handle=_findfirst(curr.c_str(),&filefind))==-1)
		  	return 0; 			    
          while(!(done=_findnext(handle,&filefind)))   
          {   
          			//printf("²âÊÔµÄ--%s\n",filefind.name);
                  if(!strcmp(filefind.name,"..")){
                  	
				  		continue;
                  }              
                  for(i=0;i<layer;i++)
				  		cout<<"     "; 			    	    			    	
                  if   ((_A_SUBDIR==filefind.attrib))   
                  {           
				  			//printf("----------%s\n",filefind.name);    
                          //cout<<filefind.name<<"(dir)"<<endl;   
                          //curr=path+"\\"+filefind.name;   
                         //filesearch(curr,layer+1);   
                  }   
                  else     
                  {   
					  file.push_back(filefind.name);
					  size++;
                          cout<<filefind.name<<endl;   
                  }   
          }           
          _findclose(handle);     
          return size;
  }   
  /*
  int   main()   
  {           vector<string> files;
          string   path;   
          cout<<"ÇëÊäÈëÄ¿Â¼"<<endl;   
          cin>>path;   
          filesearch(path,0,files);   
          system("PAUSE");   
          return   0;   
  }   
  */