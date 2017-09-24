<?php
/**
 * nw-home-header.php
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package includes.nw-home-header
 * @link http://www.iblynks.com
 */
$logout   = $_GET['user-logout'];
/**
 * Logout user
 */
if($logout=='true')
{
  $system   = new snSystem();
  
  if(isset($_COOKIE[NW_USER_COOKIE]))
  {    
    $system->set_cook_user('exit',NW_USER_COOKIE,'?nav=nw-jobseek');
  }
  if(isset($_COOKIE[NW_EMPLOYEE_COOKIE]))
  {    
    $system->set_cook_user('exit',NW_EMPLOYEE_COOKIE,'?nav=nw-employer');
  }
}
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
            <title>Newton | Online Recruitment System</title>
            <meta http-equiv="content-type" content="text/html;charset=utf-8" />
            <link rel="icon" href="<?php echo NW_IMAGE_URL; ?>icons/icon.png" />
            <link href='<?php echo NW_STYLE_URL?>layout.css' rel='stylesheet' type='text/css' />
            <link href='<?php echo NW_STYLE_URL?>iblynks-dailog.css' rel='stylesheet' type='text/css' />
            <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>jquery.min.js"></script>
            <?php  if(!isset($_GET['nav'])):?>
                <link href="<?php echo NW_STYLE_URL?>supersized.css" rel="stylesheet" type="text/css"/>
                <link href="<?php echo NW_STYLE_URL?>supersized.shutter.css" rel="stylesheet" type="text/css"/>
                <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>jquery.easing.min.js"></script>
                <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>supersized.3.2.7.min.js"></script>
                <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>supersized.shutter.min.js"></script>
                <script>
                    jQuery(function($){

                            $.supersized({

                                          /**
                                           * Functionality
                                           */
                                          slide_interval    :   3000,
                                          transition        :   1,
                                          transition_speed  :   750,

                                          /**
                                           * Components 
                                           */							
                                          slide_links       :   'blank',
                                          slides 	    :   [  
                                                                   // Slideshow Images													
                                                                   //{image : '<?php echo NW_DEFURL; ?>show/show-3.jpg'},
                                                                   {image : '<?php echo NW_DEFURL; ?>show/show-7.jpg'},
                                                                   //{image : '<?php echo NW_DEFURL; ?>show/show-6.jpg'}
                                                                ]

                                         });
                    });
                </script>
            <?php else :?>
                <link href='<?php echo NW_DEFURL?>css/smoothness/jquery-ui-1.10.4.custom.css' rel='stylesheet' type='text/css' />
                <link href='<?php echo NW_DEFURL?>css/jquery-ui-timepicker-addon.css' rel='stylesheet' type='text/css' />
                <script>
                    function currentUrl()
                    {  
                       var path = '<?php echo NW_DEFURL?>';

                       return path;       
                    }
                </script>
                <script type="text/javascript" src="<?php echo NW_DEFURL ?>js/jquery-ui-1.10.4.custom.js"></script>
                <script type="text/javascript" src="<?php echo NW_DEFURL ?>js/jquery-ui-timepicker-addon.js"></script>
                <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>jquery.defaultvalue.js"></script>
                <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>iblynks-0.1.js"></script>
                <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>ib-app-function.js"></script>
                <script type='text/javascript' src='<?php echo NW_SCRIPT_URL ?>engine.js'></script>
            <?php endif;?>
    </head>
    <body class='scroll-edit'>
        <div class='ovl' ></div><div class='ovl_message' ></div>
        <div class='control-top'>
            <logo><img src='images/logo/newton-logo.png' title='Newton Agency'/></logo>
            <nav>
                <ul>
                    <?php if(isset($_COOKIE[NW_USER_COOKIE])||isset($_COOKIE[NW_EMPLOYEE_COOKIE])): ?>
                         <li><a href='?user-logout=true'>Logout</a></li> 
                         <li><a href='?nav=nw-account'>My Account</a></li>
                         <?php $loggedin = "<div class='loggedIn'>Job Seeker</div>";?>
                         <?php   if(isset($_COOKIE[NW_EMPLOYEE_COOKIE])): ?>
                         <li><a href='?nav=nw-forum'>Forum</a></li>
                         <?php $loggedin = "<div class='loggedIn'>Employer</div>";?>
                         <?php endif;?>
                    <?php else :?>
                         <li><a href='?nav=nw-jobseek'>Job Seeker</a></li> 
                         <li><a href='?nav=nw-employer'>Employer</a></li> 
                    <?php endif;?>
                    <li><a href='?nav=nw-jobs'>Jobs</a></li>

                    <li><a href='#'>About us</a></li>
                    <li class='home-link'>
                        <a href='<?php echo NW_DEFURL?>' style='color:transparent'>H</a>
                    </li> 
                </ul>
            </nav>
        </div>
        <?php echo $loggedin;