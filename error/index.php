<?php
/**
 * Error File
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.connection.ib-con-set
 * @link http://www.iblynks.com
 */
/**
 * Include Configuration file
 */
include('../nw-config.php');
/**
 * Get the process
 */
$action = $_GET['action'];

$message = array(
                   '404'           => '404 page not found',
                   'access-denied' => 'Access Denied'
                );
?>
<html>
    <head>
        <style>
            .wrapper
            {
                margin        : 11% auto 0 auto;
                width         : 35%;
                font-size     : 13px;
                padding       : 25px 9px;
                background    : #EEE;
                border        : 1px solid #BBB;
                border-radius : 9px; 
                color         : #555;
                text-align    : center;
                font-family   : 'Arial'; 
            }
            
            .wrapper img
            {
              width  : 75px;
              height : 96px; 
            }
            
        </style>
    </head>
    <body>
        <div class='wrapper'>
            <p><img src='error1.png'/></p>
            <p><b><?php echo (isset($action))?$message[$action]:$message['404'];?></b></p>
        </div>
    </body>
</html>