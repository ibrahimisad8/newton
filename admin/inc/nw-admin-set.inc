<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
/**
 * 
 */
$admin_cookie = $_COOKIE[NW_ADMIN_COOKIE];
/**
 * Get Posts
 */
$posts        = sn_process_post();
/**
 * Action Class
 */
$action       = new snSystem();
/**
 * Validation
 */
if(isset($posts['change-pswd']))
{
    if(sn_valid_post($posts,array('change-pswd'),1)==3)
    {
        
        $check  = $action->getData('count','select * from nw_users where password="'.md5($posts['old-pswd']).'" and security="'.$admin_cookie.'"');
        
        if($check>0)
        {
            
            if($posts['new-pswd']==$posts['rep-pswd'])
            {
                
                $style   = 'gen-margin-one';
                
                $update  = $action->ib_update_data(
                                                   'nw_users',array('password' => md5($posts['new-pswd'])),
                                                   'where security ="'.$admin_cookie .'"'
                                                 );
                
                $message = system_message('error','An <b>error</b> occured please try again',$style);
                
                if($update==1)
                {
                  $message = system_message('success','Your <b>password</b> has been changed',$style); 
                }
                
            }
            else
            {
                $message = system_message('error','Your <b>new</b> & <b>repeat</b> password does not match',$style);
            }
            
        }
        else
        {
           $message = system_message('error','Your <b>old password</b> is invalid',$style);
        }
    }
    else
    { 
            $message = system_message('error','Please fill in required <b>*</b> fields',$style);   
    }
}
?>
<script>
    $(function(){
        /**
         * Validate 
         */        
        $('.admin-button-one').click(function(){
           
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
<div class='system-head'>
    <page><span>&raquo;</span>Change Password</page>
</div>
<?php echo $message?>
<div class='system-content'> 
    <content>
        <div class='generalFadediv'></div>    
        <div class='hold-jquery'>
          <form action='#' method='post'>
            <div class='top-content'>
                 <table class='table-one'>
                        <tr>
                            <td><label class='admin-label-one' >Old password</label></td>
                            <td><input class='admin-input-one' type='password' name='old-pswd'/></td>
                            <td><?php echo Jquery_field_msg('old-pswd')?></td>
                        </tr>
                         <tr>
                            <td><label class='admin-label-one' >New password</label></td>
                            <td><input class='admin-input-one' type='password' name='new-pswd'  /></td>
                            <td><?php echo Jquery_field_msg('new-pswd')?></td>
                        </tr>
                        <tr>
                            <td><label class='admin-label-one' >Repeat password</label></td>
                            <td><input class='admin-input-one' type='password' name='rep-pswd'  /></td>
                            <td><?php echo Jquery_field_msg('rep-pswd')?></td>
                        </tr>                       
                  </table>
            </div>
            <div class='bottom-content'>
                <input  type='submit' value='update' class='admin-button-one' name='change-pswd' />
            </div>
         </form>
      </div>
    </content>
</div>