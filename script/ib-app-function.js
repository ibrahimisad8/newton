/** 
 * @projectDescription   System function and flow
 *
 * @author   Ibrahim Isa
 * @version  0.1 
 */
 
/** 
 * @param  {string} f configuration
 * @return {string}
 * Description : configuration folder
 */
function config(f)
{

   var set = {
               localhost : '',
               webhost   : ''
             };
             
    return set[f];
}
/**
 * @param {string} data  operation to perform 
 * @param {string} type  help in displaying message
 * @return {string}
 * Description : Error & Success handler
 */
  function message(data,type)
  {
	  var ret;
          
	  switch(type)
          {
		  case 'error': 
                      
                    ret = "<div class='error' > "+data+" </div>";
                  
		  break;
		  
		  case 'success':
                      
                    ret = "<div class='success'> "+data+" </div>";
		  
		  break
		  		  
	  }
          
	  return ret; 
  }
/**
 * @param {aray} hanDler inputs
 * @param {array} message input message if error exist
 * @param {array} controls added controls
 * @return {bool} 
 */
function process_input(hanDler,message,controls)
{
    error = 0;
    
    var css_add = "Jquery-field-error";
    
    for(i=0; i<hanDler.length; i++) 
    {   
        /**
         * Variables
         **/
	var id     = hanDler[i];
	var change = $('[name='+id+']');
	var mess   = message[id];
		
        if(change.val()!=undefined)
        {
            if($.trim(change.val())=='')
            { 
                error = 1 ;
		$(change).addClass(css_add);
		$('#'+id).html(mess).fadeIn('normal');
		   
	     }else{
                 
                 if(controls[id])
                 {
                     /**
                      * Validate Email Address
                      **/
		     if(controls[id]==1)
                     {
                          var real_email = change.val();
                          
			  function isValidEmailAddress(real_email) 
                          {
                             var pattern = new RegExp(/^[+a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/i);
                             
                             return pattern.test(real_email);

                           }

                          if( !isValidEmailAddress(real_email))
                          {
                             error = 1;
                             $(change).addClass(css_add);
                             
                             $('#'+id).html("Invalid E-mail Address").fadeIn('normal');	

		          } else{
                              $(change).removeClass(css_add);
                              
                              $('#'+id).fadeOut('fast').html(" ");
                          
                                }  
		
		     }
	
	             /**
                      * Validate Number (e.g Mobile
                      **/
	             if(controls[id]==2)
                     {
                         if(isNaN(change.val()))
                         {
                             error = 1;
                             
                             $(change).addClass(css_add);
                             
                             $('#'+id).html("Please this should be numbers").fadeIn('normal');
			
		         }else{
                             $(change).removeClass(css_add);
                             
                             $('#'+id).fadeOut('fast').html(" ");
                              }
		     }
	             /**
                      * Validate Number (e.g Countries)
                      **/
	             if(controls[id]==3)
                     {
                         if(change.val()=='Not Selected')
                         {
                             error = 1;
                             
                             $(change).addClass(css_add);
                             
		             $('#'+id).html(mess).fadeIn('normal');
                             
			 }else{
                             $(change).removeClass(css_add);
                             
                             $('#'+id).fadeOut('fast').html(" ");
                              }
		
		     }		   
	             /**
                      * Validate leght (e.g Username)
                      **/
	             if (controls[id]==4)
                     {  
                         var cv = change.val().length;
                         if(5<cv&&cv<19)
                         { 
                             $(change).removeClass(css_add);
                             
                             $('#'+id).fadeOut('fast').html(" ");                               
		         }
                         else
                         {
                             error = 1;

                             $(change).addClass(css_add);

                             $('#'+id).html("Please min 6 & max 18 char").fadeIn('normal');
                         }
	              }
                      
		}else{
                    $(change).removeClass(css_add);$('#'+id).fadeOut('fast').html(" ");
                     } 
				
	   }
       }
	   
   }
	   
     if(error) return false;
     
     else return true;
	   
  }
/**
 * @param {Object} system
 * 
 */
function loadData(system)
{             
        $.ajax({
                 type     : "POST",

                 url      : system.url,

                 data     : system.data,
                 
                 dataType : system.dtyp,

                 success  : function(msg)
                            {                                  
                              system.arg(msg);
                               					
            	            } 
							
	       });
}
/**
 * Description : Handles pagination
 * 
 * @param {string} data Info to display
 * @param {int}    page The page number
 */
function paging(data,page)
{
	  
    var url      = 'load_data.php';
    var type     = $('input[name=load_pagination]').val();
    var category = $('input[name=load_pag_category]').val();
   	   
    if(page==undefined)
    {
       page=1; 
    } 
    
    loadData({'page':page,'type':type,'category':category},data,url);  
               
    $('#').live('click',function(){

               var page = $(this).attr('p');               
               all_general('disable',defined_id('button1'));
               loadData({'page':page,'type':type,'category':category},data,url);
    });           
     
} 
/**
 * Hadles jquery hide and show
 * @param {string} data
 * @param {string} elem
 **/
function showHide(data,elem)
{	 
	switch(data)
        {
        		
            case 'hide'   : $(elem).hide();break;
            case 'able'   : $(elem).removeClass('disabled').removeAttr('disabled')  ;break;
            case 'disable': $(elem).addClass('disabled').attr('disabled','disbled') ;break;
	
		
	}
	
 }
/**
 * Scroll to any position on the screen  
 * @param {string} id
 * @param {integer} speed
 */
function goToByScroll(id,speed)
{
    if(speed==undefined)speed=551;
    
    $('html,body').animate({scrollTop: $(id).offset().top},speed);
}
/**
 * Center any div on the screen
 * @param {string} data
 * @param {string} position 
 */
function center_any(data,position)
{
    jQuery.fn.center = function () 
    {
       var w = $(window);
       this.css("position",position);
       this.css("left", Math.max(0, ($(window).width() - this.outerWidth()) / 2) + "px");
       return this;
    };
    
    $(data).center();
}

function passDefault(in_one,in_two)
{

    var passClear = $(in_one);
    
    var passShow  = $(in_two);
    
    passClear.show();

    passShow .hide();

    passClear.focus(function(){
    
        passClear.hide();

        passShow.show();

        passShow.focus();

   });

   passShow.blur(function(){

        if(passShow.val() == '') 
        {

            passClear.show();

            passShow.hide();

        }
        
   });
}

function popUpwindow(url,width,height)
{   
    var newwindow;
    
    newwindow=window.open(url,'NEW FILE WINDOW','width='+width+',height='+height+',toolbar=0,menubar=0,location=0');  
    
    if (window.focus) 
    {
        newwindow.focus();
    }
}
/**
 * Showing & hiding Loading div 
 * @param {string} proc
 * @param {string} dDiv
 * @param {string} cp  
 */
function  generalLoaDiv(proc,dDiv,cp)
{
     var contProg = $(dDiv);
     
     if(proc=='show')
     {
         var wH     = $(cp);	
         var height = wH.height();
         var width  = wH.width();
         
         contProg.fadeIn().css({'width':width,'height':height});

     }
       
     if(proc=='hide')
     {
        contProg.fadeOut(); 
     }
        
	
     
}
/**
 * Showing & hiding Loading div 
 * @param {array} data
 * @param {string} type
 * @param {string} css  
 */
function controlAdmin (data,type,css)
{   
    for(i=0;i<data.length;i++)
    {
        if(type=='show')
        {   
            $('.'+data[i]).removeClass(css);
        }
        
        if(type=='hide')
        {
           $('.'+data[i]).addClass(css);  
        }
    }
    
}
/**
 * Reload page
 */
function reloadPage()
{
    location.reload(); 
}
/**
 * Showing & hiding Loading div
 * check all
 */
function checkAll()
{   
    /**
     * Single check box
     **/
    var single = '.cl';
    /**
     * Activate All
     **/
    var active = '.wow';
    /**
     * Delete button
     **/
    var delbut = $('.general-delete-sys-one');
    /**
     * When individual check box is checked
     **/
    $(single).live('click',function(){
        
	var c        = $(single+':checked').length;
	var cAll     = $(single).length;
	var checkAll = $(active);
        
	checkAll.removeAttr('checked');
        
	if(c>= cAll)
        {        
            checkAll.attr('checked','checked');
            delbut.show();
	}
        else
        {
             if(c<1)
             {                    
                delbut.hide();
             }
             else
             {       
                if(c>=2)
                {
                   delbut.show();           
                }
                else
                {                          
                   delbut.show();                            
                }
            }            
        }
	
    });
    /**
     * When actiavte all check box is checked
     **/
    $(active).live('click',function(){
       
        $("input[type='checkbox']").attr('checked',$('input[name=check_all]').is(':checked')); 
        
        var c = $(single+':checked').length;
        
            if(c<1)
            {
                delbut.hide();
            }
            else
            {
                delbut.show();
            }

    });
}
/**
 * Map checked box
 * @param {string} elem
 * @return oblect
 */
function mapElem(elem)
{
    var ids = $(elem).map(function(i,n) {return {'id':$(n).val()};}).get();
    
    return ids;
}
/**
 * Description : Show system is working in admin page 
 * 
 * @param {string} contrl data to show or display
 */ 
function adminSysworkn(contrl)
{
    
       
    this.loading = function(m)
    {   
        var bt = $('.'+butn('loader'));
        
        if(m=='show')bt.fadeIn();
            
        else bt.hide();
    };
    
    this.mes  = function(m,txt)
    {
       if(m=='show')
       {
           iblynks({ out :call_html('error',txt),width : '27%',height : '29%',type : 'Info',title : '<b>System</b>',error : true});
            
       }else{                
               iblynks_close();
            } 
    };
    
    this.showLoading = function(type)
    {
         
         var divname = (type=='show')? contrl : '';
         
         generalLoaDiv(type,'.display-progress-jquery',divname);
    };
    
};
/**
 * Description : General System configuration
 * 
 * @param {int} result type of result output
 */
adminSysworkn.prototype.jQsuccess = function(result)
{   
      if(result==1)
      {
          iblynks_close();reloadPage();
                                        
      }else{
              this.mes('show','Error Please try again');
           }   
             
};

adminSysworkn.prototype.aJax = function(res)
{   
       $.ajax({ 
                  url      : res.url, 
                  type     : 'POST', 
                  data     : res.data,
                  dataType : res.dataType,
                  success  : function(result){res.action(result); }
        }); 
             
};

/**
 * Description : Center Any Div
 * 
 * @param {string} m html element
 */
 jQuery.fn.centerIn = function (m) 
 {
     this.css("left", Math.max(0, ($(m).width() - this.outerWidth()) / 2) + "px");
     return this;
 };
/**
 * @param {object} arg  operation to perform 
 * Description : Error & Success handler
 */
 function regUser(arg)
 {
       /**
        *Process Register form
        **/        
        $('.light-button-type-one').stop().click(function(){

                /**
                 * Inputs for new link
                 **/
                var hDl  = Array('full-name','email','password');
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter full name';
                 mSg[hDl[1]] = 'Please enter your email';
                 mSg[hDl[2]] = 'Please enter your password';
                 /**
                  * Control for inputs
                  **/
                 var cRl = new Array;
                 
                 cRl[hDl[1]] = 1; cRl[hDl[2]] = 4;
                 /**
                  * Validate Forms
                  **/
                 if(process_input(hDl,mSg,cRl)===false)
                     
                 return false;
                 
                 else
                 {   
                     
                     DATA = {
                                'full-name': $('[name='+hDl[0]+']').val(),
                                'email'    : $('[name='+hDl[1]+']').val(),
                                'password' : $('[name='+hDl[2]+']').val(),
                                'message'  : $('[name="aboutme"]').val(),
                                'user'     : arg.user,
                                'type'     : 'register'
                            };
                     
                     generalLoaDiv('show','#none','.light-box-form-content');
                     
                     $('.Light-box-msg').fadeOut();
                     
                     $.ajax({
                                 url      : arg.url,
                                 type     : 'POST',
                                 data     : DATA,
                                 dataType : 'html',
                                 success  : function(result){                                              
                                           /**
                                            * Hide loading
                                            **/
                                            generalLoaDiv('hide','#none',''); 
                                            
                                            var message = function (m)
                                                          {
                                                              $('.Light-box-msg').fadeIn().html(m).centerIn('.ovl_message');
                                                          };
                                            if(result==1)
                                            {
                                                message('User already exist');
                                            }
                                            else if(result==2)
                                            { 
                                                window.location.replace(arg.redirect);
                                            }
                                            else
                                            {
                                                message('An error occured');
                                            }
                                 }
                                 
                               });
                 }
                 

        });

 }
 
/**
 * @param {object} arg  operation to perform 
 * Description : Login process
 */
 function logInuser(arg)
 {
        /**
         * Process Inputs
         **/
        
        DATA = {'username':arg.username,'secure':arg.secure,'type':arg.type,'cat':arg.cat};
        
        generalLoaDiv('show','#loading-one','.temp-hold');
        
        $.ajax({
                    url      : arg.url,
                    type     : 'POST',
                    data     : DATA,
                    dataType : 'html',
                    success  : function(result){

                        if(result==1)
                        {   
                            window.location.replace(arg.redirect);
                        }
                        else{
                              
                             iblynks({out :'Login invalid please try again',width:'368px',height:'196px',type:'warning',title:'Error',error:true});

                             generalLoaDiv('hide','#loading-one','');
                            
                        }
                    }
        });
 }
/**
 * @param {string} el1  div to make fix
 * @param {string} el2  jquery class to add or remove
 * Description : Login process
 */
 function make_fix(el1,el2)
 {
     var fixDiv =  function () 
                  {
                     var $cache = $(el1); 
                     if ($(window).scrollTop() > 100) 
                       $cache.addClass(el2); 
                     else
                       $cache.removeClass(el2);
                   };
     $(window).scroll(fixDiv); fixDiv();
 }
/**
 * @param {string} str  string data
 * Description: converts <br/> to  " "
 */ 
 function br2nl(str) 
 {
    return str.replace(/<br\s*\/?>/mg,"\n");
 }
