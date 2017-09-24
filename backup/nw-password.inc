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
 * Check if user is logged in
 */
$user    = check_user();
/**
 * Get Posts
 */
$posts    = sn_process_post();
/**
 * Action Class
 */
$action   = new snSystem();
/**
 * Validation
 */
if(isset($posts['pswd-submi']))
{
    if(sn_valid_post($posts,array('pswd-submit'),1)==3)
    {
        
        $check  = $action->getData('count',
                                   'select * from nw_users where password="'.md5($posts['old-pswd']).'" and security="'.$_COOKIE[$user].'"'
                                   );
        
        if($check>0)
        {
            
            if($posts['new-pswd']==$posts['rep-pswd'])
            {
                           
                $update = $action->ib_update_data(
                                                   'nw_users', 
                                                    array('password' => $posts['new-pswd']),
                                                   'where security ="'.$_COOKIE[$user].'"'
                                                );
                
                $message = system_message('error','An <b>error</b> occured please try again');
                
                if($update==1)
                
                    $message = system_message('success','Your <b>password</b> has been changed'); 
 
                
            }
            else
            {
                $message = system_message('error','An <b>new</b> & repeat <b>password</b> does not match');
            }
            
        }
        else
        {
           $message = system_message('error','Your <b>old password</b> is invalid');
        }
    }
}
?>

<script>
    $(function(){
        /**
         *Show the message 
         **/        

        $('.test-click').click(function(){
           
                /**
                 * Inputs for new link
                 **/
                var hDl  = Array('old-pswd','new-pswd','rep-pswd');
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter old password';
                 mSg[hDl[1]] = 'Please enter new password';
                 mSg[hDl[2]] = 'Please enter repeat password';
                 
                 if(process_input(hDl,mSg)==false)
                     
                 return false
                 
                 else
           
                 generalLoaDiv('show','.generalFadediv','.hold-jquery');
           
        });
    });
</script>

<?php DynDiv('H','Change password',true);?>

    <?php echo $message; ?>

      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                        <div class='top-content'>
                            <table class='table-one'>
                                <tr>
                                    <td><label class='label-input' >Old password</label></td>
                                    <td><input class='general-input-one' type='password' name='old-pswd'/></td>
                                    <td><?php echo Jquery_field_msg('old-pswd')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >New password</label></td>
                                    <td><input class='general-input-one' type='password' name='new-pswd' value="<?php echo $posts['new-pswd']?>" /></td>
                                    <td><?php echo Jquery_field_msg('new-pswd')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Repeat password</label></td>
                                    <td><input class='general-input-one' type='password' name='rep-pswd' value="<?php echo $posts['rep-pswd']?>" /></td>
                                    <td><?php echo Jquery_field_msg('rep-pswd')?></td>
                                </tr>
                            </table>                           
                        </div>
                        <div class='bottom-content'>
                            <input type='submit'  name='pswd-submit' class='general-but-one test-click' value='Submit'/>
                        </div>
                   </form>
               </div>
                   
      </div>

<?php DynDiv('F','','');?>

