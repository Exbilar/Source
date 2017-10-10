g++ -o rand rand.cpp
g++ -o std std.cpp
g++ -o my my.cpp
#tot=0
while true; do
		#tot+=1
        ./rand>rand.in 
        ./my<rand.in>my.out
        ./std<rand.in>std.out   
        if diff std.out my.out; then 
            printf "Accepted\n"    
        else  
            printf "Wrong Answer\n" 
            exit 0 
        fi  
done  
