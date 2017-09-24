<?php
/**
 * Sn-user-login
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package Template
 * @link http://www.iblynks.com
 */
?>

<?php DynDiv('H','Forum');?>

    <div class='account-dashboard'>
        <div class='forum-design'>
            
            <div id='forum-top'>
                <a href='#' class='forum-button'>New Topic</a>
            </div>
            
            <div id='forum-middle'>
                <h3>
                    Welcome To Our Web Development help and discussion forum
                </h3>
                    The forum provides help and discussion topics e.t.c. 
                    It's a friendly place to get the help you need (or help others!).

                    If you don't have an account, 
                    <span style='cursor:pointer'><b>register</b></span> now 
                    to start using the forum. We look forward to seeing you around the forum.
            </div>
            
            <div id='forum-bottom' >
                <table class='tab_admin'>
                    <tr><th width='49%'>Forum</th><th>Topics</th><th>Posts</th><th width='25%'>Last Post</th></tr>
                    <!-- 
                         <tr><td></td><td></td><td></td><td></td></tr>
                         <tr><td></td><td></td><td></td><td></td></tr>
                    -->
                </table>
                <div id='empty-tread'>
                    <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                    <p>No data yet</p>
                </div>
            </div>
            
        </div>
    </div>

<?php DynDiv('F','');?>

