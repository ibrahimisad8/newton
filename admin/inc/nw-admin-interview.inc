<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
/**
 * Include Javascript class
 */
include(NW_JHTML_CLASS);
/**
 * Save all form elements in array
 */
$posts  = sn_process_post();
/**
 * General Class
 */
$action = new snSystem();
/**
 * Initialize Class
 */
$jhtml  = new jscript();
/**
 * Query
 */
$query = 'select * from nw_applicants';
/**
 * Data
 */
$data  = $action->getData('all',$query.' order by id desc','');
?>
<script>
    $(function(){
        /**
        * Check Box
        */ 
        checkAll();
        /**
         * Delete Job Adds
         */
        $('.del-jobs').live('click',function(){

            var cbox  = $('.cl:checked');
            /**
             *  Check if at least one job has been checked
             */
            var check = cbox.length;

            if(check>0)
            {
                $('.process-loading').show(); 
                
                var ids  = mapElem('.cl:checked');

                var info = {
                             type  : 'delete',
                             table : 'nw_applicants',
                             data  : ids    
                           };

                $.ajax({
                          url  : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                          type : 'POST',
                          data : info,
                          success : function(result){

                                        if(result==1)
                                        {
                                            window.location.replace('<?php NW_ADMIN_URL.'?nav=nw-admin-reg'?>');
                                        }
                                        else
                                        { 
                                            iblynks({out :'Cannot delete please try agin later',width:'368px',height:'196px',type:'warning',title:'Error',error:true});

                                            $('.process-loading').hide(); 
                                        } 
                                    }
                          });
            }
            else
            {
               iblynks({
                          out    : 'Please choose at least one Job Application <br/><br/> to <b>delete</b>',
                          width  : '368px',
                          height : '196px',
                          type   : 'warning',
                          title  : 'Error',
                          error  : false
                      });               
            }

        });
    });
</script>
<div class='system-head'>
    <page><span>&raquo;</span>Interviews</page>
</div>
<div class='system-content'> 
    <content>
        <?php if($data['count']==0):?>
        <div class='system-loading-one'>
             <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
             <p>No data yet</p>
        </div>
        <?php else:?>
        <div class='generalFadediv genFadediv-border-radius'></div>    
        <div class='hold-jquery'>
            <!-- Controls -->
            <div class='link-nav'>
                 <table class='tab-one'>
                      <tr>
                           <td>
                               <a  name='new-job' class='admin-button-one del-jobs' act='new' >
                                  DELETE 
                              </a>
                          </td>
                          <td style='height:33px'>
                              <div class='process-loading'></div>
                          </td>
                      </tr>
                 </table>
            </div>
            <!-- Content --->
            <div class='top-content'>
              <!-- Filter -->
              <div class='admin-filter-title-one'>
                 <?php echo $viewall;?>
              </div>
              <div class='admin-filter-one'>
                  <form action='#' method='post'>
                      <select name='job-id'>
                          <option value='null'>BY JOB ID</option>
                      </select>
                      <select name='applicant'>
                          <option value='null'>BY APPLICANT</option>
                      </select>
                      <select name='status'>
                          <option value='null'>BY STATUS</option>                                      
                      </select>
                      <button class='submit-one' name='submit-filter' style='padding:8px 15px;'>FILTER</button> 
                  </form>                
              </div>
              <!-- Table -->
              <div class='table-min-height'>
                    <table class='tab_admin'>
                      <tr>
                        <th width='3%'>
                          <center> 
                            <input type='checkbox' name='check_all' id='checkbox-1-1' class='admin-checkbox wow'> <label for='checkbox-1-1'></label> 
                          </center>
                        </th>
                        <th>Job Id</th>
                        <th>Job title</th>
                        <th>Applicants Name</th>
                        <th>Status</th>
                        <th>Date Applied</th>
                        <th width='9%'>Action</th>
                      </tr>
                      <tr>
                        <?php 
                        /**
                         * Check box increment
                         */
                        $cat = 2;
                        /**
                         * Display the data
                         */
                        while($fetch = mysql_fetch_assoc($data['query'])): 
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
                                    <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='admin-checkbox cl' value='<?php echo $fetch['id']?>'> 
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
                                            <a href='<?php echo NW_DEFURL?>?nav=nw-viewjob&id=<?php echo $fetch['job_id']?>' target='_new'></a>
                                        </td>
                                    </tr>   
                                </table>
                              </td>
                            </tr>
                               
                        <?php  
                            $cat +=1;
                        endwhile;
                        ?> 
                      </tr>
                   </table>
              </div>
            </div>
        </div>
        <?php endif;?>
    </content>
</div>