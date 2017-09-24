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
if(isset($posts['comp-submit']))
{
    if(sn_valid_post($posts,array('comp-submit','web-url'),1)>0)
    {
        $insert = $action->ib_insert_data('nw_feedback', array(
                                                                 'id'       => $action->getData('max-col', 'select MAX(id) from nw_feedback'),
                                                                 'fullname' => $posts['full-name'],
                                                                 'email'    => $posts['email'],
                                                                 'message'  => $posts['message']                                                                 
                                                          ));

        if($insert==1)
        {
            $message = system_message('success','Your <b>profile</b> has been updated');       
        }
        else
        {   
            $message = system_message('error','An <b>error</b> occured please try again');   
        }
        
    }
    else
    { 
            $message = system_message('error','Please fill in required <b>*</b> fields');   
    }
}

/**
 * Get users data
 */
//$data = $action->getData('all','select * from nw_users where employer_id="'.$_COOKIE[$user].'"');

?>

<?php DynDiv('H','Company Profile',true);?>

<?php echo $message; ?> 

<script>
        $(function(){
            /**
             *Show the message 
             **/        

            $('[name="comp-submit"]').click(function(){

                    /**
                     * Inputs for new link
                     **/
                    var hDl  = Array(
                                       'company-name',
                                       'reg-num',
                                       'tel',
                                       'industry',
                                       'com-desc',
                                       'address',
                                       'country',
                                       'state',
                                       'city',
                                       'pcode'
                                   );
                    /**
                     * Error Message
                     **/
                     var mSg = new Array;

                     mSg[hDl[0]] = 'Please enter company name';  mSg[hDl[1]] = 'Please enter registration No';
                     mSg[hDl[2]] = 'Please enter telephone No.'; mSg[hDl[3]] = 'Please select industry';
                     mSg[hDl[4]] = 'Please enter description';   mSg[hDl[5]] = 'Please enter address';
                     mSg[hDl[6]] = 'Please select country';      mSg[hDl[7]] = 'Please enter state';
                     mSg[hDl[8]] = 'Please enter city';          mSg[hDl[9]] = 'Please enter postcode';
                     
                    /**
                     * Control for inputs
                     **/
                     var cRl = new Array;

                     cRl[hDl[2]] = 2; cRl[hDl[3]] = 3; cRl[hDl[6]] = 3;                   

                     if(process_input(hDl,mSg,cRl)==false)

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
                                    <td><label class='label-input' >Company Name</label></td>
                                    <td><input class='general-input-one' type='text' name='company-name' value=''/> *</td>
                                    <td><?php echo Jquery_field_msg('company-name')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Website url</label></td>
                                    <td><input class='general-input-one' type='text' name='web-url' value=''/>  </td>
                                    <td><?php echo Jquery_field_msg('web-url')?></td>
                                </tr>                                
                                <tr>
                                    <td><label class='label-input' >Registration No.</label></td>
                                    <td><input class='general-input-one' type='text' name='reg-num' value='' /> *</td>
                                    <td><?php echo Jquery_field_msg('reg-num')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Telephone</label></td>
                                    <td><input class='general-input-one' type='text' name='tel'  value='' /> *</td>
                                    <td><?php echo Jquery_field_msg('tel')?></td>
                                </tr>                               
                                <tr>
                                    <td><label class='label-input' >Industry</label></td>
                                    <td>
                                        <select class='general-input-one' name='industry' style='width:297px'>
                                            <option value='Not Selected'>Select Industry</option>
                                            <option value='1'>Business & Finance</option>
                                            <option value='2'>Computing& IT</option>
                                        </select>*
                                    </td>
                                    <td><?php echo Jquery_field_msg('industry')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Company Description</label></td>
                                    <td><textarea class='general-input-one' name='com-desc'></textarea> *</td>
                                    <td><?php echo Jquery_field_msg('com-desc')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Address</label></td>
                                    <td><textarea class='general-input-one' name='address'></textarea> *</td>
                                    <td><?php echo Jquery_field_msg('address')?></td>
                                </tr>
                                 <tr>
                                    <td><label class='label-input' >Country</label></td>
                                    <td>
                                        <select class='general-input-one' name='country' style='width:297px'>
                                            <option value='Not Selected'>Select country</option>
                                            <option value='male'>Nigeria</option>
                                            <option value='female'>Saudi Arabia</option>
                                        </select>*
                                    </td>
                                    <td><?php echo Jquery_field_msg('country')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >State</label></td>
                                    <td><input class='general-input-one' type='text' name='state'  value='' /> *</td>
                                    <td><?php echo Jquery_field_msg('state')?></td>
                                </tr>
                                 <tr>
                                    <td><label class='label-input' >City</label></td>
                                    <td><input class='general-input-one' type='text' name='city'  value='' /> *</td>
                                    <td><?php echo Jquery_field_msg('city')?></td>
                                </tr>
                                 <tr>
                                    <td><label class='label-input' >Postcode</label></td>
                                    <td><input class='general-input-one' type='text' name='pcode'  value='' /> *</td>
                                    <td><?php echo Jquery_field_msg('pcode')?></td>
                                </tr>                                
                            </table>                           
                        </div>
                        <div class='bottom-content'>
                            <input type='submit'  name='comp-submit' class='general-but-one test-click' value='Submit'/>
                        </div>
                   </form>
               </div>
                   
      </div>

<?php DynDiv('F','','');?>

