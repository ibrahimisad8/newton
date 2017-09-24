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

/**
 * Include Javascript class
 */
include(NW_JHTML_CLASS);
/**
 * Initialize Class
 */
$jhtml = new jscript();

?>

<?php DynDiv('H','Job Seeker');?>
<script>


    $(function(){
        /**
         * Register new employer
         **/        
        $('.reg-button').click(function(){

           /**
            * Show light box
            **/
           var display = {
                            content : '<?php echo compress_page($jhtml->dContent('register'))?>',
                            button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                         }
           iblynks({out :display,width:'639px',height:'395px',type:'header',title:'register'});  

           /**
            * Register arguments
            **/
           regUser({
                       user      : '3',
                       url       : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                       redirect  : '<?php echo NW_DEFURL.'?nav=nw-account';?>'

                   })

        });

        /**
         * Register new employer
         **/  
          $('.login-button').click(function(){ 

                 logInuser({
                              username : $('[name="job-seeker-username"]').val(),
                              secure   : $('[name="job-seeker-password"]').val(),
                              type     : 'login',
                              cat      : '3',
                              url      : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                              redirect  : '<?php echo NW_DEFURL.'?nav=nw-account';?>'

                           })
          });



    });
</script>
    <div class='jobSeeker'>
        <div class='left-job'>
            <div id='hold-cont'>
                <h2>Newton online recruitment agency system offers job seekers the following</h2>
                <p>
                <ul>
                    <li>Variety of jobs</li>
		    <li>Simple job search</li>
         	    <li>Easy and fast registration</li>
		    <li>Various employment options</li>
	            <li>Job matching</li>

                </ul>
                </p>
                <p >
                    <div style='padding-left: 25px' class='emp-but-hold'>
                     <a href='#' class='but-two reg-button' style='border-radius:3px '>Click here to register</a>
                    </div>
                </p>
            </div>
        </div>
        <div class='right-job'>
          <div class='generalFadediv' id='loading-one'></div>
            <div class='temp-hold' style='height:293px'>
            <div class='jobSeeker-hold'>
                <h2> Job Seeker Login </h2>
                <p> <br/><input type='text' class='jobs-input' name='job-seeker-username'/></p>
                <p> <br/><input type='password' class='jobs-input' name='job-seeker-password'/></p>
                <p> <br/><input type='submit' class='jobs-input jobs-inputs-submit login-button'  value='LOGIN'/></p>
                <p> <a href='#' >Forgot your password</a> </p>
            </div>
        </div>
    </div>
    </div>
<?php DynDiv('F','');?>

