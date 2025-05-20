## Precursor for running the file: 

Client and server has the code to run the pipeline. Make sure server code is running before running Client code. 
Purpose of the Server is to be able to run python libraries natively for ML training 
Eventually we want to be able to convert these python files into CPP for less bottlenecking 
Docker file is to make sure we can make this a container in Raspi, requirements has our required files. 



## HOW TO RUN: 

Make sure to run this one time before you run the following 
``` chmod +x .devtools/run.sh ``` 
or alternatively if you're already in the .devtools folder
```  chmod +x run.sh ``` 


Anytime you want to run the code, simply put this into the terminal: 
``` cd .devtools ```
Then run the following to  run the full system: Docker server + client
``` make run ``` 
To run solely the client run 
``` make client ``` 
To run solely the server run 
``` make server ``` 

## Common errors: 
if you get 
``` ▶️  Starting full system (Docker server + client)...  
./run.sh  
make: ./run.sh: Permission denied  
make: *** [run] Error 1 ```

make sure that you ran 
``` chmod +x .devtools/run.sh ``` 

prior to running ``` make run ``` 

