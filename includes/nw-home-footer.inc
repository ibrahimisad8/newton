<?php
/**
 * Sn-home-header.php
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package includes.nw-home-footer
 * @link http://www.iblynks.com
 */
?>
<?php  if(isset($_GET['nav'])):?>
        <div class='footer'> 
            &copy; Copyright Newton <?php echo date('Y');?>.
        </div>
<?php endif;?>
    </body>    
</html><?php ob_end_flush();?>