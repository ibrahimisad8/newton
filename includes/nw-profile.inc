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
$user     = check_user();
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
if(isset($posts['profile-submit']))
{
    if($posts['full-name'])
    {
        $update  = $action->ib_update_data('nw_users', array(
                                                                 'fullname' => $posts['full-name'],
                                                                 'gender'   => $posts['gender'],
                                                                 'about'    => $posts['message']                                                                 
                                                          ),'where security="'.$_COOKIE[$user].'"');
        
        
        
        
        if($update==1)
        {
            $message = system_message('success','Your <b>profile</b> has been updated');
            
        }
        else{
            
            $message = system_message('error','An <b>error</b> occured please try again');
           
        }
    }
}

/**
 * Get users data
 */
$data = $action->getData('array','select * from nw_users where security="'.$_COOKIE[$user].'"');

?>

<?php DynDiv('H','Profile',true);?>

<?php echo $message; ?> 

<script>
        $(function(){
            /**
             *Show the message 
             **/        

            $('[name="profile-submit"]').click(function(){

                    /**
                     * Inputs for new link
                     **/
                    var hDl  = Array('full-name');
                    /**
                     * Error Message
                     **/
                     var mSg = new Array;

                     mSg[hDl[0]] = 'Please enter full name';

                     if(process_input(hDl,mSg,'')==false)

                     return false

                     else

                     generalLoaDiv('show','.generalFadediv','.hold-jquery');

            });
        });
</script>
      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                        <div class='top-content'>
                            <table class='table-one'>
                                <tr>
                                    <td><label class='label-input' >Full name</label></td>
                                    <td><input class='general-input-one' type='text' name='full-name' value='<?php echo $data['fullname']?>'/></td>
                                    <td><?php echo Jquery_field_msg('full-name')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Email</label></td>
                                    <td><input class='general-input-one' type='text' name='email' disabled='disabled' value='<?php echo $data['email']?>' /></td>
                                    <td></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Gender</label></td>
                                    <td>
                                        <select class='general-input-one' name='gender' style='width:297px'>
                                            <option value='male'>Male</option>
                                            <option value='female' <?php echo ($data['gender']=='female')?'selected="selected"':''?> >Female</option>
                                        </select>
                                    </td>
                                    <td></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >About me</label></td>
                                    <td><textarea class='general-input-one' name='message'><?php echo $data['about']?></textarea></td>
                                    <td></td>
                                </tr>
                            </table>                           
                        </div>
                        <div class='bottom-content'>
                            <input type='submit'  name='profile-submit' class='general-but-one test-click' value='Submit'/>
                        </div>
                   </form>
               </div>
                   
      </div>

<?php DynDiv('F','','');?>

