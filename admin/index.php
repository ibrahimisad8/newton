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
<!DOCTYPE html>
<html>
    <head>
        <title>Newton | Administrator</title>
        <link rel="icon" href="<?php echo NW_IMAGE_URL; ?>icons/icon.png" />
        <!-- General home css style -->
        <link href='<?php echo NW_STYLE_URL?>message.css' rel='stylesheet' type='text/css'/>
        <link href='<?php echo NW_STYLE_URL?>jscript.css' rel='stylesheet' type='text/css'/>        
        <!-- Admin css style -->
        <link href='style/admin-layout.css' rel='stylesheet' type='text/css'/>
        <link href='<?php echo NW_STYLE_URL?>iblynks-dailog.css' rel='stylesheet' type='text/css' />
        <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>jquery.min.js"></script>
        <script>
             function currentUrl()
             {  
                  var path = '<?php echo NW_DEFURL?>';

                  return path;       
              }
        </script>
        <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>iblynks-0.1.js"></script>
        <script type="text/javascript" src="<?php echo NW_SCRIPT_URL ?>ib-app-function.js"></script>
    </head>
        <?php 
            /**
             *  Check if Admin is logged in
             */
            if(isset($_COOKIE[NW_ADMIN_COOKIE]))
            {
                /**
                 * Include Header file
                 */
                include NW_ADMIN_HEADER ;
                /**
                 * Dynamic Content
                 */
                 dynamicSys('GET',NW_ADMIN_DYN,'inc','nw-admin-control','nav');
                /**
                 * Include Footer
                 */
                include NW_ADMIN_FOOTER;   
                
            }else{
                
                /**
                 *  Include Login Page
                 */
                include (NW_ADMIN_LOGIN);
            
            }


        ?>
</html>

<?php endif; ?>