<?php
/**
 * Sn-user-login
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package includes.nw-home-header
 * @link http://www.iblynks.com
 */

$posts    = sn_process_post();

$action   = new snSystem();
/**
 * Login Validations
 */
if(isset($posts['login-submit']))
{
    if($posts['login-username']&&$posts['login-password'])
    {
        $data = $action->getData('all','select * from nw_users where email="'.$posts['login-username'].'" and password="'.md5($posts['login-password']).'"');
    
        if($data['count']>0)
        {   
            
            if($data['fetch']['category']=='3'||$data['fetch']['category']=='2')
            {
                if($data['fetch']['category'])
                    
                $cookie = NW_USER_COOKIE;
                
                if($data['fetch']['category'])
                    
                $cookie = NW_EMPLOYEE_COOKIE;
                
                $action->set_cook_user($cookie,$data['fetch']['security'],'?nav=nw-account');
                
            }else{
            
                $message = system_message('error','An error occured please try again','alt-design');
            }
            
        }else{
            
            $message = system_message('error','Invalid Username or password','alt-design');
        }
        
    }
}
?>

<?php DynDiv('H','Login');?>
<script>


$(function(){
    /**
     *Show the message 
     **/        
    
    $('.test-click').click(function(){
       iblynks({out : '<span style="font-size:17px">Please fill in the required fields</span>',width:'27%',height:'29%',type:'warning'});  

    });
    
    
});
</script>
            <?php echo $message; ?>
            <div class='account-dashboard'>
               <div class='account-login'>
                    <div class='inputs-home-hold'>
                        <div method='POST' action='#'>
                            <p>Username<br/><input type='text' name='login-username' class='test-click' /></p>
                            <p>Password<br/><input type='password' name='login-password' /></p>
                            <p><center><span><input type='submit'  name='login-submit' class='com' value='Login'/></span></center></p>                            
                            <p><center><a href='#'>Forgot Password</a></center></p>
                        </div>
                    </div>
                </div>
            </div>
<?php DynDiv('F','Login');?>
