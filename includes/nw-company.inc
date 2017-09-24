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
    if(sn_valid_post($posts,array('comp-submit','web-url'),1)==10)
    {
        
        $update = $action->ib_update_data('nw_organization', array(                                                            
                                                                    'company'      => $posts['company-name'], 
                                                                    'url'          => $posts['web-url'], 
                                                                    'business_no'  => $posts['reg-num'], 
                                                                    'telephone'    => $posts['tel'], 
                                                                    'industry'     => $posts['industry'], 
                                                                    'company_desc' => $posts['com-desc'], 
                                                                    'location'     => $posts['address'], 
                                                                    'country'      => $posts['country'], 
                                                                    'state'        => $posts['state'],
                                                                    'city'         => $posts['city'],
                                                                    'postcode'     => $posts['pcode'],
                                                                    'gate'         => '1'
                                                                  ),'where employer="'.$_COOKIE[$user].'"');

        if($update==1)
        {
            $message = system_message('success','Your <b>Company profile</b> has been updated');       
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
$data = $action->getData('array','select * from nw_organization where employer="'.$_COOKIE[$user].'"');
?>

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

                     mSg[hDl[0]] = 'Please enter company name';  mSg[hDl[1]] = 'Please enter registration no.';
                     mSg[hDl[2]] = 'Please enter telephone no.'; mSg[hDl[3]] = 'Please select industry';
                     mSg[hDl[4]] = 'Please enter description';   mSg[hDl[5]] = 'Please enter address';
                     mSg[hDl[6]] = 'Please select country';      mSg[hDl[7]] = 'Please enter state';
                     mSg[hDl[8]] = 'Please enter city';          mSg[hDl[9]] = 'Please enter postcode';
                     
                    /**
                     * Control for inputs
                     **/
                     var cRl = new Array;

                     cRl[hDl[2]] = 2; cRl[hDl[3]] = 3; cRl[hDl[6]] = 3;                   

                     if(process_input(hDl,mSg,cRl)==false)

                     return false;

                     else

                     generalLoaDiv('show','.generalFadediv','.hold-jquery');

            });
        });
</script>

<?php DynDiv('H','Company Profile',true);?>

<?php echo $message; ?> 

      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                        <div class='top-content'>
                            <table class='table-one'>
                                <tr>
                                    <td><label class='label-input' >Company Name</label></td>
                                    <td><input class='general-input-one' type='text' name='company-name' value='<?php echo $data['company']?>'/> *</td>
                                    <td><?php echo Jquery_field_msg('company-name')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Website url</label></td>
                                    <td><input class='general-input-one' type='text' name='web-url'  value='<?php echo $data['url']?>'/>  </td>
                                    <td><?php echo Jquery_field_msg('web-url')?></td>
                                </tr>                                
                                <tr>
                                    <td><label class='label-input' >Registration No.</label></td>
                                    <td><input class='general-input-one' type='text' name='reg-num' value='<?php echo $data['business_no']?>' /> *</td>
                                    <td><?php echo Jquery_field_msg('reg-num')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Telephone</label></td>
                                    <td><input class='general-input-one' type='text' name='tel'  value='<?php echo $data['telephone']?>' /> *</td>
                                    <td><?php echo Jquery_field_msg('tel')?></td>
                                </tr>                               
                                <tr>
                                    <td><label class='label-input' >Industry</label></td>
                                    <td>
                                        <select class='general-input-one' name='industry' style='width:297px'>
                                            <option value='Not Selected'>Select Industry</option>
                                            <?php industry_list($data['industry'],false) ?>
                                        </select>*
                                    </td>
                                    <td><?php echo Jquery_field_msg('industry')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Company Description</label></td>
                                    <td><textarea class='general-input-one' name='com-desc'><?php echo $data['company_desc']?></textarea> *</td>
                                    <td><?php echo Jquery_field_msg('com-desc')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >Address</label></td>
                                    <td><textarea class='general-input-one' name='address'><?php echo $data['location']?></textarea> *</td>
                                    <td><?php echo Jquery_field_msg('address')?></td>
                                </tr>
                                 <tr>
                                    <td><label class='label-input' >Country</label></td>
                                    <td>
                                        <select class='general-input-one' name='country' style='width:297px'>
                                            <option value='Not Selected'>Select country</option>
                                            <?php counties_list('custom',$data['country'],false)?>
                                        </select>*
                                    </td>
                                    <td><?php echo Jquery_field_msg('country')?></td>
                                </tr>
                                <tr>
                                    <td><label class='label-input' >State</label></td>
                                    <td><input class='general-input-one' type='text' name='state'  value='<?php echo $data['state']?>' /> *</td>
                                    <td><?php echo Jquery_field_msg('state')?></td>
                                </tr>
                                 <tr>
                                    <td><label class='label-input' >City</label></td>
                                    <td><input class='general-input-one' type='text' name='city'  value='<?php echo $data['city']?>' /> *</td>
                                    <td><?php echo Jquery_field_msg('city')?></td>
                                </tr>
                                 <tr>
                                    <td><label class='label-input' >Postcode</label></td>
                                    <td><input class='general-input-one' type='text' name='pcode'  value='<?php echo $data['postcode']?>' /> *</td>
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

