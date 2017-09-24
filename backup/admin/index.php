<?php
/**
 * Admin Index
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.connection
 * @link http://www.iblynks.com
 */

 $filename = 'nw-load-admin.php';

 if(file_exists($filename)):
     
 include $filename;
 
 ?>
<html>
    <head>
        <title>Newton | Administrator</title>
        <link href='style/admin-layout.css' rel='stylesheet' type='text/css'/>
        <link rel="icon" href="<?php echo NW_IMAGE_URL; ?>icons/icon.png" />
    </head>
        <?php 

            /**
             *  Set Default Page 
             */
            $default = NW_ADMIN_LOGIN;
            /**
             *  Check if Admin is logged in
             */
            if(isset($_COOKIE[NW_ADMIN_COOKIE]))
            {
                 // Set Admin Page
                 $default =  NW_ADMIN_CONTROL;       
            }

            /**
             *  Include Default
             */
            include ($default);
        ?>
</html>

<?php endif;?>