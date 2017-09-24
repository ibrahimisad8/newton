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
 * Sucsses Message key
 */
$success = false;
/**
 * Validation
 */
if(isset($posts['feed-submit']))
{
    if($posts['email']&&$posts['subject']&&$posts['message'])
    {
        $insert = $action->ib_insert_data('nw_feedback', array(
                                                                 'id'       => $action->getData('max-col', 'select MAX(id) from nw_feedback'),
                                                                 'user'     => $_COOKIE[$user],
                                                                 'email'    => $posts['email'],
                                                                 'subject'  => $posts['subject'],
                                                                 'message'  => $posts['message'],
                                                                 'date'     => sn_date('real',4) 
                                                          ));
        
        if($insert)
        {
            $message = '';
            
            $success = true;
        }
        else{
            
            $message = system_message('error','An <b>error</b> occured please try again');
           
        }
    }
}

$data = $action->getData('array','select * from nw_users where security="'.$_COOKIE[$user].'"');

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
                var hDl  = Array('subject','email','message');
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter subject';
                 mSg[hDl[1]] = 'Please enter email';
                 mSg[hDl[2]] = 'Please enter message';
                 /**
                  * Control for inputs
                  **/
                 var cRl = new Array;
                 
                 cRl[hDl[1]] = 1;
                 
                 if(process_input(hDl,mSg,cRl)==false)
                     
                 return false
                 
                 else
           
                 generalLoaDiv('show','.generalFadediv','.hold-jquery');
           
        });
    });
</script>

<?php DynDiv('H','Feedback',true);?>
    <?php echo $message; ?> 
      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <?php if($success==1): ?>
                        <div class='general-success'>
                            <div id='top'>
                                <p>
                                    <img src='<?php echo NW_IMAGE_URL?>icons/feed.png' />
                                </p>
                            </div>
                            <div id='bottom'>
                                <p>Message sent thank you we will get</p>
                                <p>back to you soon</p>
                            </div>
                        </div>
                   <?php else:?>
                   <form action='#' method='post'>
                        <div class='top-content'>
                            <table class='table-one'>
                                <tr>
                                    <td><label class='label-input' >Email</label></td>
                                    <td>
                                        <input class='general-input-two' type='text' name='view-email' value='<?php echo $data['email']?>' disabled='disabled'/>
                                        <input type='hidden' name='email' value='<?php echo $data['email']?>'/>
                                    </td>
                                    <td><?php echo Jquery_field_msg('email')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Subject</label></td>
                                    <td><input class='general-input-two' type='text' name='subject'/></td>
                                    <td><?php echo Jquery_field_msg('subject')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Message</label></td>
                                    <td>
                                        <textarea class='general-input-two' name='message' style='height:127px'></textarea>
                                    </td>
                                    <td><?php echo Jquery_field_msg('message')?></td>
                                </tr>
                            </table>                           
                        </div>
                        <div class='bottom-content'>
                            <input type='submit'  name='feed-submit' class='general-but-one test-click' value='Submit'/>
                        </div>
                   </form>
                   <?php endif;?>
               </div>
                   
      </div>

<?php DynDiv('F','');?>

