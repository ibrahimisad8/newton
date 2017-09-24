<?php
/**
 * Sn-register
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package includes.nw-home-header
 * @link http://www.iblynks.com
 */

/**
 * Get Posts
 */
$posts    = sn_process_post();

/**
 * Action Class
 */
$action   = new snSystem();

/**
 * Resgister Validations
 */
if(isset($posts['reg-submit']))
{  
    if($posts['reg-fullname']&&$posts['reg-email']&&isset($posts['reg-password']))
    {
    
        $data  = $action->getData('count','select * from nw_users where email="'.$posts['reg-email'].'"');

        if($data>0)
        {
          $message = system_message('error','User Already Exist','alt-design');

        }else{
             
                   
                $insert = $action->ib_insert_data('nw_users', array(
                                                                      'id'       => $action->getData('max-col', 'select MAX(id) from nw_users'),
                                                                      'fullname' => $posts['reg-fullname'],
                                                                      'email'    => $posts['reg-email'],
                                                                      'password' => md5($posts['reg-password']),
                                                                      'category' => $posts['reg-category'],
                                                                      'security' => $action->randoms()
                                                                    ));
                
                $message = system_message('error','An error occured please try again' ,'alt-design');
                
                if($insert)
                
                $message = system_message('success','Registered successfully please login','alt-design');
                
                $posts['reg-fullname']    = '';
                
                $posts['reg-email']       = '';
                
                $posts['reg-password']    = '';
                
                $posts['reg-category']    = '3';
                                  

       }
    
    }else{
        
        $message = system_message('error','Please fill in all feilds','alt-design');
    }
}

?>

<?php DynDiv('H','Register');?>
           <?php echo $message; ?>
           <div class='account-dashboard'>
               <div class='account-login'>
                    <div class='inputs-home-hold'>
                        <form method='POST' action='#'>
                            <p>Full Name<br/><input type='text' name='reg-fullname' value='<?php echo $posts['reg-fullname']?>'/></p>
                            <p>Email<br/><input type='text' name='reg-email' value="<?php echo $posts['reg-email']?>"/></p>
                            <p>Password<br/><input type='password' name='reg-password' value="<?php echo $posts['reg-password']?>" /></p>
                            <p>
                                Category<br/>
                                <select name='reg-category'>
                                    <option value='3' <?php echo($posts['reg-category']=='3')?'selected':'';?>>Job Seeker</option>
                                    <option value='2' <?php echo($posts['reg-category']=='2')?'selected':'';?>>Employer</option>
                                </select>
                            </p>
                            <p><center><span><input type='submit'  name='reg-submit' class='com' value='Register'/></span></center></p>
                        </form>
                    </div>
                </div>
           </div>
<?php DynDiv('F','Register');?>

