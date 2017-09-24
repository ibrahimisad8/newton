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
 * Action Class
 */
$action   = new snSystem();
/**
 * Initialize Class
 */
$jhtml = new jscript();
/**
 * Data
 */
$data    = true;
?>vv

<script>

    $(function(){
        /**
         * Add new job
         **/ 
        checkAll();

       $('[name="new-job"]').click(function(){

            /**
             * Show light box
             **/
             var display = {
                                 content : '<?php echo compress_page($jhtml->dContent('add-job'))?>',
                                 button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                           }

            iblynks({out :display,width:'639px',height:'395px',type:'header',title:'NEW JOB'});
            
            /**
             * Process new job
             */
            $('.light-button-type-one').click(function(){
                
                /**
                 * Inputs for new link
                 **/
                var hDl  = Array('job-title','desc');
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter job title';
                 mSg[hDl[1]] = 'Please enter job description';
                 
                 if(process_input(hDl,mSg)==false)
                     
                 return false
                 
                 else
                 { 

                     
                     var info = {
                                    'job-title' : $('[name='+hDl[0]+']').val(),
                                    'desc'      : $('[name='+hDl[1]+']').val(),
                                    'type'      : 'new-job'
                                 };
                     /**
                      *Loading
                      */
                     generalLoaDiv('show','#none','.light-box-form-content');
                     
                     $('.Light-box-msg').fadeOut();
                     
                     $.ajax({
                                 url      : '<?php echo NW_DEFURL.NW_JAVA.'/'?>',
                                 type     : 'POST',
                                 data     : info,
                                 dataType : 'html',
                                 success  : function(result){                                              
                                           /**
                                            * Hide loading
                                            **/
                                            generalLoaDiv('hide','#none',''); 
                                            
                                            var e_message = function (m)
                                                          {
                                                              $('.Light-box-msg').fadeIn().html(m).centerIn('.ovl_message');
                                                          }
                                            if(result==1)
                                            
                                              e_message('System is working'); 
                                             
                                            else
                                                
                                              e_message('An error occured');
                                 }
                                 
                               });

                 }
                
            });

       });


    });

</script>

<?php DynDiv('H','Job Advertisement',true);?>

    <?php //echo $message; ?> 

      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                       <div class='link-nav'>
                         <table class='tab-one'>
                          <tr>
                            <td>
                            <a  name='new-job' class='general-but-one' >
                              ADD NEW  
                            </a>
                           </td>
                           <td>
                            <a name='feed-submit' class='general-but-one' >
                              DELETE 
                            </a>
                           </td>
                         </tr>
                         </table>
                       </div>
                       <div class='top-content'>
                           <?php if($data==0):?>
                                <div class='system-loading-one'>
                                     <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                                     <p>No data yet</p>
                                </div>
                           <?php else:?>
                                <table class='tab_admin'>
                                    <tr>
                                        <th width='3%'>
                                            <center> 
                                                <input type='checkbox' name='check_all' id='checkbox-1-1' class='regular-checkbox wow'> <label for='checkbox-1-1'></label> 
                                            </center>
                                        </th>
                                        <th>Job title</th>
                                        <th>Industry</th>
                                        <th>Date</th>
                                        <th width='15%'>Action</th>
                                    </tr>
                                    <tr>
                                        <td>
                                            <center> 
                                                <input type='checkbox' id='checkbox-1-2' class='regular-checkbox cl'> <label for='checkbox-1-2'></label> 
                                            </center>
                                        </td>
                                        <td></td>
                                        <td></td>
                                        <td></td>
                                        <td></td>
                                    </tr>
                                    <tr>
                                        <td>
                                            <center> 
                                                <input type='checkbox'  id='checkbox-1-3' class='regular-checkbox cl'> <label for='checkbox-1-3'></label> 
                                            </center>
                                        </td>
                                        <td></td>
                                        <td></td>
                                        <td></td>
                                        <td></td>
                                    </tr>                               
                                </table>
                         <?php endif;?>
                       </div>
                   </form>
               </div>     
      </div>

<?php DynDiv('F','');?>

