<?php
/**
 * Sn-user-login
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package Template
 * @link http://www.iblynks.com
 */
/**
 * Include Javascript class
 */
include(NW_JHTML_CLASS);
/**
 * Initialize Class
 */
$jhtml = new jscript();
?>

<?php DynDiv('H','Employer');?>

<script>


$(function(){
    /**
     * Register new employer
     */        
    $('.reg-button').click(function(){
        
       /**
        * Show light box
        */
       var display = {
                        content : '<?php echo compress_page($jhtml->dContent('register'))?>',
                        button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                     };
                     
       iblynks({out :display,width:'639px',height:'395px',type:'header',title:'register'});  
       
       /**
        * Register arguments
        */
       regUser({
                   user      : '2',
                   url       : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                   redirect  : '<?php echo NW_DEFURL.'?nav=nw-account';?>'
                   
               });

    });
    
    /**
     * Login Employer
     */  
     $('.login-button').click(function(){ 
             
             logInuser({
                          username : $('[name="emp-login-username"]').val(),
                          secure   : $('[name="emp-login-password"]').val(),
                          type     : 'login',
                          cat      : '2',
                          url       : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                          redirect  : '<?php echo NW_DEFURL.'?nav=nw-account';?>'
                          
                       })
      });
    
    
    
});
</script>

<div class='employer'>
    <div class='home'>
        <div class='left'>
            <div class='hm-content'>
                <h2>No 1 Jobs Website</h2>
                <div class='small-cont'>
                    Think Jobs,Place an ad<br/> 
                    with Newton and get your jobs in front of far more job seekers than any other site.
                    Sign up today and post an ad that works
                </div>
                <div class='emp-but-hold'>
                    <a href='#' class='but-one'>Post a job now for free</a><a href='#' class='but-two'>See how it works</a>
                </div>
            </div>
        </div>
        <div class='right'>
            <div class='generalFadediv' id='loading-one'></div>
            <div class='temp-hold' style='height:296px'>
                <div class='emp-inputs-hold'>
                    <p class='emp-advertiser'> ADVERTISERS LOGIN</p>
                    <p><br/><input type='text'     name='emp-login-username' class='emp-inputs'/></p>
                    <p><br/><input type='password' name='emp-login-password' class='emp-inputs'/></p>
                    <p><br/><input type='submit'   name='emp-login-submit'  class='emp-inputs emp-inputs-submit login-button' value='LOGIN'/></p>
                    <p>Forgot your password ?  - OR -  <span style='cursor:pointer' class='reg-button'>Register</span></p>
                </div>
            </div>
        </div>
    </div>
</div>
<div class='account-dashboard' style='overflow:hidden'>
    <div class='employer-down'>
        <div class='child'>
          <table valign='top'>
              <tr>
                  <td><img src='<?php echo NW_IMAGE_URL?>icons/1.png' /></td>
                  <td>
                      <h2>Screening Tool</h2>
                      <div id='info-top'>Use this to quickly select the most qualified applicants for your jobs.</div>
                      <div id='info-bot'><a href='#'> Learn More </a></div>
                  </td>
              </tr>
          </table>  
        </div>
        <div class='child'>
           <table>
              <tr>
                  <td><img src='<?php echo NW_IMAGE_URL?>icons/2.png' /></td>
                  <td>
                      <h2>CV Database</h2>
                      <div id='info-top'>
                          Reach qualified candidates in no time.
                          Even if they don't apply for your jobs
                      </div>
                      <div id='info-bot'><a href='#'> Learn More </a></div>
                  </td>
              </tr>
          </table>
        </div>
        <div class='child' style='border-right: 0px'>
           <table>
              <tr>
                  <td><img src='<?php echo NW_IMAGE_URL?>icons/3.png' /></td>
                  <td>
                      <h2>Monitor </h2>
                      <div id='info-top'>Get the most out of Newton Online Application</div>
                      <div id='info-bot'><a href='#'> Learn More </a></div>
                  </td>
              </tr>
          </table>
        </div>
    </div>
</div>

<?php DynDiv('F',''); ?>

