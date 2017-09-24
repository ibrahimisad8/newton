<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
/**
 * Check if admin is loogged in
 */
$admin  = NW_ADMIN_COOKIE;
/**
 * General system class
 */
$system = new snSystem();
/**
 * Logout Admin
 */
$logout = $_GET['admin-logout'];

if($logout==$_COOKIE[$admin])
{
   $system->set_cook_user('exit',$admin,'admin');     
}
?>

<body class='body-body scroll-edit'>

    <div class='ovl' ></div><div class='ovl_message' ></div>

    <!-- Admin Top Control -->

    <div class='system-control'>
        <nav>
            <ul>
                <li style="border-right:1px solid #777">
                    <span class='spn_link' style='width:78px'>
                        <img class='is_img' style='top:7px' src='<?php echo NW_ADMIN_IMG.'icon' ?>/newton-logo-admin.png'/>
                    </span>
                </li>
                <li>
                    <a href='<?php echo NW_DEFURL?>' target='_new'>
                        <span class='spn_link' style='width:24px'>
                            <img class='is_img' style='top:7px' src='<?php echo NW_ADMIN_IMG.'icon' ?>/globe.png' title='Go to homepage'/>
                        </span>
                    </a>
                </li>
                <li><a href='<?php echo NW_ADMIN_URL?>'>Menu</a></li>
                <li><a href='#'>Help</a></li>
                 <li><a href='#'>About</a></li>
            </ul>
        </nav>
        <nav class='nav-right'>
            <ul>
                <li>
                    <a href='<?php echo NW_ADMIN_URL?>?admin-logout=<?php echo $_COOKIE[NW_ADMIN_COOKIE]?>'>
                        Logout
                    </a>
                </li>
            </ul>
        </nav>
    </div>

    <!--- Display --->

    <div class='admin-wrapper'>
    
