/** 
* @projectDescription   Home page jquery - javascript
* @author   Ibrahim Isa
* @version  0.1 
*/
$(function() {

            /**
             * @Element     : window
             * @action      : scroll function 
             * @Description : This shows scroll to the top element
             */

          $(window).scroll(function() {

                    var elm  = $('.scrollTotop');

                    if ($('body').height() <= ($(window).height() + $(window).scrollTop())) 
                    {
                       elm.stop().fadeIn('normal');

                    }else{
                          
                       elm.stop().fadeOut('normal');
                          
                    } 

           });

      
           /**
            * @Element     : general-postion
            * @action      : on[clcik] function 
            * @Description : This handles scroll to any point in th epage  
            */            
           $('.general-position').click(function(){
               
                  var toGo = $(this).attr('p');
                  
                  goToByScroll(toGo);
               
               
           });          
      
          /**
           * @Element     : defaultValue
           * @Description : Values input field which must hav default values  
           */

           $(".test").defaultvalue("Keyword, Job title");
           
          /**
           * @Element     : defaultValue
           * @Description : Employer Login Username
           */
                         
           $("input[name=emp-login-username]").defaultvalue("Email");
                          
          /**
           * @Element     : defaultValue
           * @Description : Employer Login Password
           */
                         
           $("input[name=emp-login-password],input[name=job-seeker-password]").defaultvalue("password");
           
          /**
           * @Element     : defaultValue
           * @Description : Employer Login Password
           */
                         
           $("input[name=job-seeker-username]").defaultvalue("Email");
           
           /**
            * @Element     : img
            * @Description : Wait for images to load then fade them In
            */
           $('.wait img').load(function (event) {
                
                //setTimeout(function(){
                             
                            $(event.target).fadeIn(1500); 
                             
                                    // }, 5000);
           
           });
                   
              
                       
});

