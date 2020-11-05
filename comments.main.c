                 
                  
                  
                       

                 
    /**
     * 
     * Prints help
    */
                        
                                                   
 

                                                    

    /**
     * 
     * Function that does all the io
     * reads filename
     * writes to newfilename
     * 
    */
                    //pointer on filename
                     //pointer on newfilename
                //variables that hold characters for testing and writing
                                          //initialise state of cursor to outside comment.. entry state
                                //holds previous insidecandidate state
                                 //holds previous outsidecomment state


                                     //if filename is openned for reading succesfully

                                            // if newfilename is openned for writing successfully

                                         //read characters one at a time from filename

                                        //set the cursor state for the current character

                                         //if we are outside of comments
                    
                                            //reinnitialize previous inside candidate state
                                             //if the previous state was OUTSIDECANDIDATE
                                                          //move cursor 2 chars back  
                                       //read previously omitTed char OUTSIDECANDIDATE
                                       //write it to newfilename
                                       //read a char == c
                                       //write it to newfilename
                                                 //set prev state to 0
                     
                         //if it wasnt a candidate
                                    //if it's a line break
                                      //write it
                                             //if its any other character print a space
                                                                       //if we are inside a comment whatever it's type
                                                                   
                        /**
                         * in both cases where the cursor was OUTSIDECANDIDATE or INSIDECANDIDATE
                         * we need to write the previous character since it's inside a comment
                         * 
                        */
                                                          //take cursor 2 chars back
                                       //read previously omitTed char
                                       //write it
                                                          //move the cursor one char (c)
                                                 //reset both previous states
                                             


                     
                                  //write c
                                                                    //if the cursor is pointing on a candidate to a comment start save that state 
                                                                       //if the cursor is pointing on a candidate to a comment end save that state 
             

                        //close newfilename
         
              //error handling for opening for reading problems (ex: permissions)
                                                            
                                              
                               
         

                   //close filename

     
          //error handling for opening for reading problems (ex: permissions)
                                                        
                                       

                           
     


 

                                                                             

    /**
     * Parses arguments and alters filename and newfilename
     * 
     * 
    */
                  
                 //if only on arg is suplied (executable name)
            // handle error
                                                  
                        
                               
                  
                //if one extra argument is suplied (missing newfilename)
                                   //point to it using filename
             //allocate memory for newfilename as big as the size of filename plus a "comments." copied to the beginning
                                                                                               
                                               //put comments. in the beginning
                                             //add filename after comment.
                  
                //if 2 extra arguments are suplied
            //just point to them
                                  
                                     
                  
                 //if more arguments -> too many arguments and print help
                                               
                        


     
 

                                 

   

                                               

                                                     //parse command line arguments

                                       //remove code
    
    //Garbage Collection
                                                       
             
 