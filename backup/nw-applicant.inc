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
 * Check if user is logged in
 */
$user    = check_user();
/**
 * Save all form elements in array
 */
 $posts = sn_process_post();
/**
 * General Class
 */
$action = new snSystem();
/**
 * Initialize Class
 */
$jhtml = new jscript();
/**
 * Process filter
 */
if(isset($posts['submit-filter']))
{       
        $setFilter =''; $Cfilter = 0;
        /**
         * Check Job id filter
         */
        if(!empty($posts['jobid'])&&$posts['jobid']!=='null')
        {   
            $setFilter .= ' and job_id="'.$posts['jobid'].'"';
            $Cfilter +=1;
        }
        /**
         * Check Applicant filter
         */
        if(!empty($posts['applicant'])&&$posts['applicant']!=='null')
        {   
            $setFilter .= ' and user_id="'.$posts['applicant'].'"';
            $Cfilter +=1;
        }
        /**
         * Check Status
         */
        if(!empty($posts['status'])&&$posts['status']!=='null')
        {   
            $setFilter .= ' and status="'.$posts['status'].'"';
            $Cfilter +=1;
        } 
        /**
         * Check if filter is used
         */
        if($Cfilter>0)
        {
            $viewall = "<a href='".NW_DEFURL."?nav=nw-applicant'>View All</a>";
        }
        
}
/**
 * Query
 */
$query = 'select * from nw_applicants where employer_id="'.$_COOKIE[$user].'"'.$setFilter;
/**
 * Data
 */
$jobdata      = $action->getData('all',$query.' order by id desc','');
/**
 * Filter set by job id
 */
$JobidFilter  = $action->getData('query',$query.' group by job_id');
/**
 * Filter set by user id
 */
$UsridFilter  = $action->getData('query',$query.' group by user_id');
/**
 * Filter set by user id
 */
$StatusFilter = $action->getData('query',$query.' group by status');
?>

<script>

    $(function(){
        
       /**
        * Display message 
        */
        var nw_app_msg  = function(m,e)
                             {
                                iblynks({
                                           out    : m,
                                           width  : '368px',
                                           height : '196px',
                                           type   : 'warning',
                                           title  : 'Error',
                                           error  : e
                                       });
                             }
       /**
        * Loading gif
        */
        var nw_app_load  = function(t)
                         {
                            generalLoaDiv(t,'#none','.light-box-form-content');
                         } 
       /**
        * Make dix to fixed position
        */
        make_fix('.link-nav','fix-div-one');
       /**
        * Check Box
        */ 
        checkAll();
       /**
        * Application status
        */
        $('[name="action-done"]').change(function(){
            
                var cbox    = $('.cl:checked');
                /**
                 * Check if at least one job is checked
                 */
                var check   = cbox.length;
            
                if(check>0)
                {       
                    
                    var actionID  = $(this).val();
                    
                    if(actionID!=='null')
                    {
                        
                        $('.process-loading').show(); 

                        var ids  = mapElem('.cl:checked');

                        var info = {
                                      table  : 'nw_applicants',
                                      data   : ids ,
                                      type   : 'update',
                                      action : actionID,
                                      col    : 'status'
                                   };

                        var url_link = '<?php echo NW_JQUPDEL ?>';

                        $.ajax({
                                   url  : url_link,
                                   type : 'POST',
                                   data : info,
                                   success : function(result){

                                                     if(result==1)
                                                     {
                                                         window.location.replace('<?php NW_DEFDIR.'?nav=nw-applicant'?>');
                                                     }
                                                     else
                                                     { 
                                                         nw_app_msg('Cannot perform action please try agin later',true);

                                                         $('.process-loading').hide(); 
                                                     } 

                                    }
                              });
                     }
               }
               else
               {
                  nw_app_msg('Please select at least one job application to <br/><br/>to perform action',false);
                  
                  $(this).val('nul');
               }
          });
       /**
        * View applicant data
        */
        $('.applicant').click(function(){
            
            
            var info = { 
                          id  : $(this).attr('p'),
                          key : 'jason-user-cont' 
                       };
            
                          
            $.ajax({
                       url      : '<?php echo NW_DEFURL.NW_JAVA.'/nw-load.php'?>',
                       type     : 'POST',
                       data     :  info,
                       dataType : 'json',             
                       success  : function(result){
                                  
                                  if(result.success==1)
                                  {   
                                      var display = {content : result.content}
                                      
                                      iblynks({out :display,width:'639px',height:'395px',type:'header',title:result.header});  
                                  }
                                  else
                                  {
                                     nw_app_msg('An erro occured please try agin later',false); 
                                  }

                               
                         }   
                    });

            
            
        });
       /**
        * Schedule interview
        */
        $('.interview').click(function(){
            
            /**
             * Action to resend or schedule interview
             **/
            var action = $(this).attr('act');
            /**
             * The title of light box
             **/
            var dtitle =(action=='edit')? 'RE-SCHEDULE INTERVIEW' : 'SCHEDULE INTERVIEW'; 
            /**
             * Get application ID
             **/       
            var aid   = $(this).attr('p');
            /**
             * Get users id
             **/       
            var usr   = $(this).attr('usr');
            /**
             * Get job title
             **/       
            var jit   = $(this).attr('jit');
            /**
             * Get users email
             **/       
            var eml   = $(this).attr('eml'); 
            /**
             * Show light box
             **/
            var display = {
                              content : '<?php echo compress_page($jhtml->dContent('interview',$user))?>',
                              button  : '<?php echo compress_page($jhtml->dButtons())?>'                             
                           }

            iblynks({out :display,width:'819px',height:'495px',type:'header',title: dtitle});
            /**
             * Light box inputs
             **/
             var hDl  = Array('app-data','job-title','interview-date','interview-msg');
            /**
             * Update fields
             */
            $('[name='+hDl[0]+']').val(usr);
             
            $('[name='+hDl[1]+']').val(jit);
            
            $('[name='+hDl[3]+']').val('Good day '+usr);
            /**
             * Date & time  picker
             */
            $('[name="interview-date"]').datetimepicker({timeFormat: "hh:mm tt"});
            /**
             * Process input field
             */
            $('.light-button-type-one').click(function(){
                
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter Applicants';
                 mSg[hDl[1]] = 'Please enter job title';
                 mSg[hDl[2]] = 'Please click to enter date';
                 mSg[hDl[3]] = 'Please enter message';
                 
                 if(process_input(hDl,mSg,'')==false)
                     
                 return false
                 
                 else
                 {   
                     var date = $('[name='+hDl[2]+']').val();
                     
                     var mesg = $('[name='+hDl[3]+']').val();
    
                     var comp = $('[name="company"').val(); 
                     
                     var job  = $('[name='+hDl[1]+']').val();
                     
                     var e_subject = 'NEWTON AGENCY - JOB INTERVIEW';
                     
                     var send_email = '<p><b>NEWTON MANGEMENT TEAM</b></p>'+
                                      '<p><b>Dear '+usr+'</b></p>'+
                                      '<p>'+
                                          'You are scheduled to have an interview with the <b>employer</b> as shown '+
                                          'below please follow the employers guide or info.'+
                                      '</p><br><br>'+
                                      '<p><b>EMPLOYERS INFORMATION</b></p>'+
                                      '<p><b>Job Title</b><br>'+job+'</p>'+
                                      '<p><b>Interview date</b><br/>'+date+'</p>'+
                                      '<p><b>Meassage</b><br/>'+mesg+'</p>'+
                                      '<p><b>Companys name & Contact </b><br/>'+comp+'</p>';
                                      
                     var info = {   
                                    'date'   : date,
                                    'send_e' : send_email, 
                                    'e_title': e_subject,
                                    'jobt'   : job,  
                                    'app'    : aid,
                                    'type'   : 'interview'
                                };
                    /**
                     * Loading
                     */
                     nw_app_load('show');
                     
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
                                                                                        
                                            var e_message = function (m)
                                                          {
                                                              $('.Light-box-msg').fadeIn().html(m).centerIn('.ovl_message');
                                                          }
                                            if(result==1)
                                            {
                                                var  data = {
                                                                email   : eml,
                                                                subject : e_subject,
                                                                msg     : send_email
                                                            };                

                                                 $.ajax({

                                                          url      : 'http://www.iblynks.com/newton/mail.php',
                                                          type     : 'POST',
                                                          data     :  data,
                                                          dataType : 'html',
                                                          success  : function(result)
                                                          {

                                                               if(result==1)
                                                               {
                                                                    window.location.replace('<?php NW_DEFDIR.'?nav=nw-applicant'?>');
                                                               }
                                                               else
                                                               {
                                                                  nw_app_load('hide');e_message('An error occured could not send <b>email</b>');
                                                               }

                                                          }
                                                 }); 
                                            } 
                                            else
                                            {
                                               nw_app_load('hide'); e_message('An error occured');
                                            }
                                 }
                                 
                       });
                       

                 }
                
            });
            
        });
        
    });

</script>

<?php DynDiv('H','Applicants',true);?>

<div class='general-content'>
        
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                     <?php if($jobdata['count']==0):?>
                        <div class='system-loading-one'>
                                 <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                                 <p>No data yet</p>
                        </div>
                    <?php else: ?>
                    <!--- Controls --->
                     <div class='link-nav'>
                         <table class='tab-one'>
                          <tr>
                            <td>
                            <select  name='action-done' class='general-select-one' act='add' >
                                <option value='null'>ACTIONS</option>
                                <option value='1'>Pending</option>
                                <option value='3'>Rejected</option>
                                <option value='4'>Employed</option>
                            </select>
                            </a>
                            <input  name='company'type='hidden' value="<?php echo userDetails('organization',$_COOKIE[$user])?>"/>
                           </td>
                           <td style='height:33px'>
                               <div class='process-loading'></div>
                           </td>
                         </tr>
                         </table>
                       </div>
                        <div class='top-content'>
                            <div class='filter-title-one'>
                                <?php echo $viewall;?>
                            </div>
                            <div class='filter-type-one'>
                                <form action='#' method='POST'>
                                    <select name='jobid'>
                                       <option value='null'>BY JOB ID</option>
                                       <?php 
                                           while($FJobid = mysql_fetch_assoc($JobidFilter))
                                           {   
                                               
                                              echo "<option value='".$FJobid['job_id']."' ".selected($FJobid['job_id'],$posts['jobid']).">
                                                       ".job_id($FJobid['job_id'])."
                                                   </option>";
                                           }
                                        ?>
                                    </select>
                                    <select name='applicant'>
                                        <option value='null'>BY APPLICANT</option>
                                        <?php 
                                           while($FusrID = mysql_fetch_assoc($UsridFilter))
                                           {
                                               /**
                                                * Applicants Name
                                                */
                                                $appData = $action->getData('array','select * from nw_users where security="'.$FusrID['user_id'].'"');

                                                echo "<option value='".$appData['security']."' ".selected($appData['security'],$posts['applicant'])." >
                                                        ".$appData['fullname']."
                                                      </option>";
                                           }
                                        ?>
                                    </select>
                                    <select name='status'>
                                        <option value='null'>BY STATUS</option>
                                       <?php 
                                           while($Fstatus = mysql_fetch_assoc($StatusFilter))
                                           {   
                                               
                                               echo "<option value='".$Fstatus['status']."' ".selected($Fstatus['status'],$posts['status']).">
                                                      ".job_status($Fstatus['status'])."
                                                     </option>";
                                           }
                                        ?>                                       
                                    </select>
                                    <button class='submit-one' name='submit-filter' style='padding:8px 15px;'>FILTER</button>
                                </form>
                            </div>
                            <div class='table-min-height'>
                                  <table class='tab_admin'>
                                    <tr>
                                        <th width='3%'>
                                            <center> 
                                                <input type='checkbox' name='check_all' id='checkbox-1-1' class='regular-checkbox wow'> <label for='checkbox-1-1'></label> 
                                            </center>
                                        </th>
                                        <th>Job Id</th>
                                        <th>Job title</th>
                                        <th>Applicants Name</th>
                                        <th>Status</th>
                                        <th>Date Applied</th>
                                        <th width='15%'>Action</th>
                                    </tr>
                                    <?php 
                                      /**
                                       * Check box increment
                                       */
                                      $cat = 2;
                                      /**
                                       * Display the data
                                       */
                                      while($fetch = mysql_fetch_assoc($jobdata['query']))
                                      {   
                                          /**
                                           * Get job title & others
                                           */                                          
                                          $job_title = $action->getData('array','select * from nw_jobs WHERE id="'.$fetch['job_id'].'"');
                                          /**
                                           * Job status
                                           */
                                          $status    = job_status($fetch['status']);
                                          /**
                                           * Applicants data
                                           */
                                          $applicant = $action->getData('array','select * from nw_users where security="'.$fetch['user_id'].'"');
                                          ?> 
                                                <tr>
                                                    <td>
                                                        <center> 
                                                            <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='regular-checkbox cl' value='<?php echo $fetch['id']?>'> 
                                                            <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                                        </center>
                                                    </td>
                                                    <td><?php echo job_id($job_title['id'])?></td>
                                                    <td><?php echo ucwords($job_title['job_title'])?></td>
                                                    <td><?php echo ucwords($applicant['fullname'])?></td>
                                                    <td><span class='<?php echo $status?>'><?php echo $status?></span></td>
                                                    <td><?php echo sn_date('change',6,$fetch['date'])?></td>
                                                    <td>
                                                        <table width='100%' class='table_actions'>
                                                         <tr>
                                                             <td class='view' title='View job advert'>
                                                                 <a href='?nav=nw-viewjob&id=<?php echo $fetch['job_id']?>&act=nw-applicant'></a>
                                                             </td>
                                                             <td class='applicant' title='View applicants data' p="<?php echo $applicant['id']?>"></td>
                                                             <td class='interview' title='Schedule Interview'   
                                                                 p='<?php echo $fetch['id']?>' jit='<?php echo $job_title['job_title']?>' 
                                                                 usr='<?php echo $applicant['fullname']?>' eml='<?php echo $applicant['email']?>'
                                                                 act='new'
                                                             ></td>
                                                         </tr>   
                                                        </table>
                                                    </td>
                                                </tr>
                                             
                                          <?php
                                          
                                          $cat +=1;
                                      }
                                    ?> 
                                  </table>
                            </div>
                        </div>
                    <?php endif;?>
               </div>
                   
      </div>

<?php DynDiv('F','');?>

