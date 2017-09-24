<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
$system = new snSystem();

$logout = $_GET['admin-logout'];
/**
 * Logout Admin
 */
if($logout==$_COOKIE[NW_ADMIN_COOKIE])
{
  $system->set_cook_user('exit',NW_ADMIN_COOKIE,'admin');        
}

?>
<body class='body-body scroll-edit'>
    
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
    
    <!------ Head ------>
    
    <div class='system-head'>
        <page><span>&raquo;</span>Dashboard</page>
    </div>
    
    <!----- Content ----->
    
    <div class='system-content'>
        <function>
        <a class='child' href='#'>
            <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/address-one.png')" ></i>
            <h3>Account Information</h3>
        </a>
        <a class='child' href='#'>
            <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/inter.png')" ></i>
            <h3>Interviews</h3>
        </a>
        <a class='child child-end' href='#'>
             <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/forum.png')" ></i>
            <h3>Forum</h3>
        </a>
        <a class='child' href='#'>
             <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/user-one.png')" ></i>
            <h3>Manage Users</h3>
        </a>
        <a class='child' href='#'>
             <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/email-2.png')" ></i>
            <h3>Notifications</h3>
        </a>
        <a class='child child-end' href='#'>
            <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/products.png')" ></i>
            <h3>Jobs Inventory</h3>
        </a>
        <a class='child' href='#'>
             <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/report.png')" ></i>
            <h3>Reports</h3>
        </a>
        <a class='child' href='#'>
             <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/database.png')" ></i>
            <h3>System Backup</h3>
        </a>
        <a class='child child-end' href='#'>
            <i style="background-image:url('<?php echo NW_ADMIN_FUNIMG?>/settings-2.png')" ></i>
            <h3>General Settings</h3>
        </a>
        </function>
    </div>
    
    <!------ Footer ------>
    
    <div class='system-footer'>&COPY; Newton Agency <?php echo date('Y')?></div>
    
</div>
</body>