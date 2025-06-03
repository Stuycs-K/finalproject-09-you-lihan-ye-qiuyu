[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/am3xLbu5)
# MD5 algorithm
 
### MP4? No. MD5.

Li Han You, Leo Ye
       
### Project Description:

Our project is a recreation of the MD5 encryption tool. Our program will take any string and convert it into a 128-bit hash.
We also created our own version of hashcat, using our MD5 encryption tool. 
  
### Instructions:

You have two options when running our hash program:   
1. Input your own string    
`make hash ARGS="YOUR_STRING"`
2. Use a preset string     
`make hash ARGS="PRESET [1-3]"`

You can also crack your hash using our hashcat:  
*Note: We recommend using the rockyou pwd list*            
`make hashcat ARGS="YOUR_HASH PWD_LIST"`

### Resources/ References:

1. [Amazing Youtube Video By Rareskills](https://www.youtube.com/watch?v=5MiMK45gkTY)
2. [GeeksforGeeks](https://www.geeksforgeeks.org/what-is-the-md5-algorithm/)   
3. [Wikipedia](https://en.wikipedia.org/wiki/MD5) 
4. [Markdown Syntax Guide](https://www.markdownguide.org/basic-syntax/)

We used the Wikipedia and GeeksforGeeks as a starter for MD5, allowing use to understand the general gist of MD5.
However, it was confusing and hard to visualize the way the bitwise operations worked using their explanations. 

So we used the video as a guide since the animations clarified any confusion we had of the process.
The video also did a great job breaking down the more layered portions of the encryption.    