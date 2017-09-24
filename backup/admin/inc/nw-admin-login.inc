<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */

$action = sn_process_post();

$query  = new snSystem();

if(isset($action['Submit']))
{
    if($action['username']&&$action['password'])
    {
      
        $data = $query->getData('all','select * from nw_users where username="'.$action['username'].'" and password="'.md5($action['password']).'"');
    
        if($data['count']>0)
        {
            $query->set_cook_user(NW_ADMIN_COOKIE,$data['fetch']['security'],'admin');
            
        }else{
            
            $message = system_message('error','Invalid Username or password','');
        }
        
    }
}

?>
 <body class='body-home'>
       <div class='login-admin'>
            <div id='top'><?php echo ($_GET['user']==true)? "Employer Login" : "Administrator"?></div>
            <div id='bottom'>                
                <form action='#' method='POST'>
                    <div id='message_handler'><?php echo($message);?></div>
                    <div id='hold-input' style='margin-top:5px' title='Username' >
                        <div id='ic_on' class='usr_name'  ></div>
                        <div id='d_input'>
                            <input type='text' name='username' value='<?php echo $action['username']?>'/>
                        </div>
                    </div>
                    <div id='hold-input' title='Password' >
                        <div id='ic_on' class='password' ></div>
                        <div id='d_input'>
                            <input type='password' name='password'/>        
                        </div>
                    </div>
                    
                    <div>
                        <input type='submit' name='Submit' value=' Login' class='button_style_one' />
                    </div>            
                </form>
            </div>
        </div>
        <div class='footer-login'>
            <table>
                <tr>
                    <td width='20%'><a href='<?php echo NW_DEFURL?>' target='<?php echo ($_GET['user']==true)? "_parent" : "_new"?>'><span style='font-size:19px'>&cularr;</span> Go to Website </a></td>
                    <td width='60%' id='cen_ter'></td>
                    <td width='20%' id='right_dat'> &COPY; Newton Agency</td>
                </tr>
            </table> 
        </div>
    </body>