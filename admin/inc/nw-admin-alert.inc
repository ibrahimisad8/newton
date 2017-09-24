<?php
/**
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @link http://www.iblynks.com
 */
/**
 * Save all form elements in array
 */
$posts = sn_process_post();
/**
 * General Class
 */
$action = new snSystem();
/**
 * Set filter
 */
if(isset($posts['submit-filter']))
{
        $setFilter =''; $Cfilter = 0;
        /**
         * Check Job seeker filter
         */
        if(!empty($posts['job-seek'])&&$posts['job-seek']!=='null')
        {   
            $setFilter .= ' where user="'.$posts['job-seek'].'"';
            
            $Cfilter +=1;
        }
        /**
         * Check if filter is used
         */
        if($Cfilter>0)
        {
            $viewall = "<a href='".NW_ADMIN_URL."?nav=nw-admin-alert'>View All</a>";
        }        
}
/**
 * Query
 */
$query = 'select * from nw_feedback'.$setFilter;
/**
 * Data
 */
$data  = $action->getData('all',$query.' order by id desc','');
/**
 * Filter set by job seeker
 */
$JobseekFilter  = $action->getData('query',$query.' group by user');
?>
<script>

    $(function(){
        
       /**
        * Display message
        */
        var nw_admin_alt  = function(m,e)
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
        * Make dix to fixed position
        */
        make_fix('.link-nav','fix-div-one');
       /**
        * Add new job
        */ 
        checkAll();       
       /**
        * Delete messages
        */
        $('.del-feedback').live('click',function(){
            
                var cbox    = $('.cl:checked');
                /**
                 * Check if at least one job is checked
                 */
                var check   = cbox.length;
            
                if(check>0)
                        {
                        $('.process-loading').show(); 

                        var ids  = mapElem('.cl:checked');

                        var info = {
                                      type  : 'delete',
                                      table : 'nw_feedback',
                                      data  : ids    
                                    };

                          $.ajax({

                                  url  : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                                  type : 'POST',
                                  data : info,
                                  success : function(result){

                                                 if(result==1)
                                                 {
                                                     window.location.replace('<?php NW_ADMIN_URL.'?nav=nw-admin-alert'?>');
                                                 }
                                                 else
                                                 { 
                                                     nw_admin_alt('Cannot delete please try agin later',true);

                                                     $('.process-loading').hide(); 
                                                 } 

                                }
                          });
                  }
                  else
                  {
                      nw_admin_alt('Please select at least one feedback to <br/><br/><b>delete</b>',false);
                  }
        });
       /**
        * View messages
        */
        $('.view-feedback').live('click',function(){ 
           
           /**
            * User sent to
            **/
            var sento   = $(this).attr('name');
            
            var style   = 'style="height:345px;font-size:11px;border-bottom:1px dotted #BBB"';
            
            var message = '<div class="light-box-general-content" '+style+'>'+
                             '<div class="norm-title-email">Subject</div>'+
                             '<div class="norm-msg">'+
                                $(this).attr('subj')+
                             '</div>'+
                             '<div class="norm-title-email">Message</div>'+
                             '<div class="norm-msg">'+
                                $(this).attr('mesg')+
                             '</div>'+
                          '</div>';
           /**
            * Show light box
            **/
            iblynks({
                       out    : {content : message},
                       width  : '685px',
                       height : '485px',
                       type   : 'header',
                       title  : 'FROM : '+sento
                   });
        });
       /**
        * Submit filter loading
        */ 
        $('[name="submit-filter"]').click(function(){
            
            generalLoaDiv('show','.generalFadediv','.hold-jquery');
            
        });   
        
        
          
    });

</script>
<div class='system-head'>
    <page><span>&raquo;</span>Feedbacks</page>
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
           <div class='link-nav'>
                <table class='tab-one'>
                     <tr>
                          <td>
                              <a  name='new-job' class='admin-button-one del-feedback' act='new' >
                                 DELETE 
                             </a>
                         </td>
                         <td style='height:33px'>
                             <div class='process-loading'></div>
                         </td>
                     </tr>
                </table>
          </div>       
          <div class='top-content' >
              <div class='admin-filter-title-one'>
                 <?php echo $viewall;?>
              </div>
              <div class='admin-filter-one'>
                  <form action='#' method='post'>
                        <select name='job-seek'>
                              <option value='null'>BY JOB SEEKER</option>
                                    <?php 
                                         while($FjobsID = mysql_fetch_assoc($JobseekFilter))
                                         {
                                              /**
                                               * Jobseekers Name
                                               */
                                               $appData = $action->getData('array','select * from nw_users where security="'.$FjobsID['user'].'"');

                                               echo "<option value='".$appData['security']."' ".selected($appData['security'],$posts['job-seek'])." >
                                                        ".$appData['fullname']."
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
                                <input type='checkbox' name='check_all' id='checkbox-1-1' class='admin-checkbox wow'> <label for='checkbox-1-1'></label> 
                             </center>
                            </th>
                           <th>Job seeker</th>
                           <th>Email</th>
                           <th>Subject</th>
                           <th>Date</th>
                           <th width='7%'>Action</th>
                        </tr>
                           <?php 
                              /**
                               * Check box increment
                               */
                               $cat = 2;
                              /**
                               * Display the data
                               */
                               while($fetch = mysql_fetch_assoc($data['query']))
                               {
                                   $user = $action->getData('array','select * from nw_users where security="'.$fetch['user'].'"');
                           ?> 
                                    <tr>
                                        <td>
                                           <center> 
                                              <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='admin-checkbox cl' value='<?php echo $fetch['id']?>'> <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                            </center>
                                        </td>
                                        <td><?php echo ucwords($user['fullname']) ?></td>
                                        <td><?php echo $fetch['email']?></td>
                                        <td><?php echo $fetch['subject']?></td>
                                        <td><?php echo sn_date('change',3,$fetch['date'])?></td>
                                        <td>
                                            <table width='100%' class='table_actions'>
                                               <tr>
                                                   <td class='edit view-feedback' title='Edit Industry' 
                                                        name='<?php echo $user['fullname']?>'
                                                        subj='<?php echo ucwords($fetch['subject'])?>'
                                                        mesg='<?php echo ucwords($fetch['message'])?>'>
                                                   </td>
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
        </div>
      <?php endif;?>
    </content>
</div>