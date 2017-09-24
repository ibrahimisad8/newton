<?php
/**
 * Sn-account
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package includes.nw-home-header
 * @link http://www.iblynks.com
 */
/**
 * Check if user is logged in
 */
$user    = check_user();
/**
 * Check for warnings
 */
$check   = nw_special_check($user.'_home_warn');
/**
 * Set warning message
 */
//$message = ($check!==0)? $check : ''; 
//Check if user has updated his company profile
if($check!==0)
{
    $style   = 'sys-error'; 
    $url     = 'javascript:void(0)';
    $message = $check;
}
else
{
    $message = $style = $url = '';
}
?>
<script>
    $(function(){
        /**
         *Show warning message 
         **/        
        $('.sys-error').click(function(){
           
           iblynks({
                      out    : 'Please update your <b>company</b> profile<br/><br/> to continue',
                      width  : '368px',
                      height : '196px',
                      type   : 'warning',
                      title  : 'System error'
                  });
           
        });
    });
</script>
<?php DynDiv('H','My Account');?>
    
    <?php echo $message; ?> 

    <div class='users-home'>
        
       <?php 
           if($user==NW_EMPLOYEE_COOKIE)
           {  
              // Company profile
              home_functions('?nav=nw-company','inter.png','Company Profile');
              // Job advertisments
              home_functions((!empty($url))?$url:'?nav=nw-jobads','job_list.png','Job Advertisement',$style);
              // Employees
              home_functions('?nav=nw-applicant','candi.png','Applicants');
              //Emails
              home_functions('?nav=nw-emails','email-one.png','Notification');
           }
           else
           {  
              //Curriculum vitae
              home_functions('?nav=nw-cvitae','cv.png','Curriculum vitae');
              //Job Applications
              home_functions('?nav=nw-jobapp','job_list.png','Job Applications');
              //Help Topic
              home_functions($url,'help.png','Help Topic');
              // Alerts
              home_functions('?nav=nw-feedback','feedback.png','Feedback');
           }
            // Profile
            home_functions('?nav=nw-profile','user-2.png','My Profile');
            // Password
            home_functions('?nav=nw-password','lock-two.png','Change Password');
        ?>
      
    </div>

<?php DynDiv('F','');?>