<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
/**
 * Admin browser cookie
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
if(isset($posts['update-profile']))
{
    if($posts['full-name']&&$posts['email'])
    {   
        $style   = 'gen-margin-one';
        
        $check   = $action->getData('count','select * from nw_users where email="'.$posts['email'].'" and security!="'.$admin_cookie.'"');
        
        if($check>0)
        {
            $message = system_message('error','Sorry the <b>email</b> address already exist',$style);
        }
        else
        {
            $update  = $action->ib_update_data('nw_users', array(
                                                                  'fullname' => $posts['full-name'],
                                                                  'email'    => $posts['email'],
                                                                  'gender'   => $posts['gender'],
                                                                  'about'    => $posts['message']                                                                 
                                                                ),'where security="'.$admin_cookie.'"');




            if($update==1)
            {
                $message = system_message('success','Your <b>profile</b> has been updated',$style);

            }
            else{

                $message = system_message('error','An <b>error</b> occured please try again',$style);

            }
        }
    }
}
/**
 * Get users data
 */
$data = $action->getData('array','select * from nw_users where security="'.$admin_cookie.'"');
?>
<script>
    $(function(){
        /**
         * Validate form  
         **/        
        $('.admin-button-one').click(function(){
            
              /**
               * Inputs for new link
               **/
               var hDl  = Array('full-name','email');
              /**
               * Error Message
               **/
               var mSg = new Array;

               mSg[hDl[0]] = 'Please enter full name';
               mSg[hDl[1]] = 'Please enter email';
               /**
                * Control for inputs
                */
               var cRl = new Array;
                 
               cRl[hDl[1]] = 1;
               
               if(process_input(hDl,mSg,cRl)==false)

               return false
           
               else

               generalLoaDiv('show','.generalFadediv','.hold-jquery');
        });
    });
</script>

<div class='system-head'>
    <page><span>&raquo;</span>Account Information</page>
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
                            <td><label class='admin-label-one' >Full name</label></td>
                            <td><input class='admin-input-one' type='text' name='full-name' value='<?php echo $data['fullname']?>'/></td>
                            <td><?php echo Jquery_field_msg('full-name')?></td>
                        </tr>
                        <tr>
                            <td><label class='admin-label-one' >Email</label></td>
                            <td><input class='admin-input-one' type='text' name='email' value='<?php echo $data['email']?>' /></td>
                            <td><?php echo Jquery_field_msg('email')?></td>
                        </tr>
                        <tr>
                            <td><label class='admin-label-one' >Gender</label></td>
                            <td>
                              <select class='admin-input-one' name='gender' style='width:297px'>
                                 <option value='male'>Male</option>
                                 <option value='female' <?php echo ($data['gender']=='female')?'selected="selected"':''?> >Female</option>
                              </select>
                            </td>
                            <td></td>
                        </tr>
                        <tr>
                            <td><label class='admin-label-one' >About me</label></td>
                            <td><textarea class='admin-input-one' name='message'><?php echo $data['about']?></textarea></td>
                            <td></td>
                        </tr>
                  </table>
            </div>
            <div class='bottom-content'>
                <input  type='submit' value='update' class='admin-button-one' name='update-profile' />
            </div>
         </form>
      </div>
    </content>
</div>