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
 * Check if user is logged in
 */
$user    = check_user();
/**
 * General Class
 */
$action = new snSystem();
/**
 * Data
 */
$jobdata  = $action->getData('all','select * from nw_applicants where user_id="'.$_COOKIE[$user].'" order by id desc','');
?>

<script>

    $(function(){
        
       /**
        * Display message
        */
        var nw_jopapp_msg  = function(m,e)
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
        * Delete Job Application
        */
        $('.un-subscribe-job').live('click',function(){
            
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
                                                     window.location.replace('<?php NW_DEFDIR.'?nav=nw-jobapp'?>');
                                                 }
                                                 else
                                                 { 
                                                     nw_jopapp_msg('Cannot delete please try agin later',true);

                                                     $('.process-loading').hide(); 
                                                 } 

                                }
                          });
                  }
                  else
                  {
                      nw_jopapp_msg('Please select at least one job application to <br/><br/><b>un subscribe</b>',false);
                  }
          });
          
    });

</script>

<?php DynDiv('H','Job Applications',true);?>

      <div class='general-content'>
          
               <div class='generalFadediv genFadediv-border-radius'></div>    
               <div class='hold-jquery'>
                   <form action='#' method='post'>
                     <?php if($jobdata['count']==0):?>
                        <div class='system-loading-one'>
                                 <p><img src='<?php echo NW_IMAGE_URL?>general/data.png' /></p>
                                 <p>No data yet</p>
                        </div>
                    <?php else:?>
                    <!--- Controls --->
                     <div class='link-nav'>
                         <table class='tab-one'>
                          <tr>
                            <td>
                            <a  name='un-subscribe' class='general-but-one un-subscribe-job' act='add' >
                              UN SUBSCRIBE  
                            </a>
                           </td>
                           <td style='height:33px'>
                               <div class='process-loading'></div>
                           </td>
                         </tr>
                         </table>
                       </div>
                        <div class='top-content'>
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
                                        <th>Status</th>
                                        <th >Date Applied</th>
                                        <th width='9%'>Action</th>
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
                                          $query      = 'select * from nw_jobs WHERE id="'.$fetch['job_id'].'"';
                                          
                                          $job_inv    = $action->getData('all',$query);
                                          
                                          $job_id     = ($job_inv['count']>0)?'NW_'.leadingZeros($job_inv['fetch']['id'],job_inventory()):'NULL';
                                          
                                          $job_title  = ($job_inv['count']>0)?$job_inv ['fetch']['job_title']:'<span class="rejected">JOB DELETED</span>';
                                          /**
                                           * Job status
                                           */
                                          $status    = job_status($fetch['status']);
                                          ?> 
                                                <tr>
                                                    <td>
                                                        <center> 
                                                            <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='regular-checkbox cl' value='<?php echo $fetch['id']?>'> <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                                        </center>
                                                    </td>
                                                    <td><?php echo $job_id ?></td>
                                                    <td><?php echo ucwords($job_title)?></td>      
                                                    <td><span class='<?php echo $status?>'><?php echo $status?></span></td>
                                                    <td><?php echo sn_date('change',6,$fetch['date'])?></td>
                                                    <td>
                                                        <table width='100%' class='table_actions'>
                                                         <tr><td class='view' ><a href='?nav=nw-viewjob&id=<?php echo $fetch['job_id']?>&act=nw-jobapp'></a></td></tr>   
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
                   </form>
               </div>
                   
      </div>

<?php DynDiv('F','');?>

