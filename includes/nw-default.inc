<?php
/**
 * Sn-home-header.php
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package includes.nw-home-header
 * @link http://www.iblynks.com
 */
?>
  <div class='home-wrapper'>
                <div class='info'>
                    <h1>Online Recruitment<br/>Agency System<br/></h1>
                    <h2>Make Online Registration For Different Job Positions</h2>
                    <div class='enter'>
                        <?php if(isset($_COOKIE[NW_USER_COOKIE])||isset($_COOKIE[NW_EMPLOYEE_COOKIE])): ?>
                        <a href='?nav=nw-jobs'class='Classs2'>Search Jobs</a>
                        <?php else:?>
                        <a href='?nav=nw-jobseek'class='Classs2'>Apply Now</a>
                        <?php endif;?>
                    </div>
                </div>
  </div>

