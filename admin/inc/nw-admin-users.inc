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
 * Set Filter
 */
if(isset($posts['submit-filter']))
{
        $setFilter =''; $Cfilter = 0;
        /**
         * Check Job seeker filter
         */
        if(!empty($posts['filter']))
        {   
            $setFilter .= ' and category="'.$posts['filter'].'"';
            
            $Cfilter +=1;
        }
        /**
         * Check if filter is used
         */
        if($Cfilter>0)
        {
            $viewall = "<a href='".NW_ADMIN_URL."?nav=nw-admin-users'>View All</a>";
        } 
}
/**
 * Query
 */
$query = 'select * from nw_users where security!="'.filter_input(INPUT_COOKIE,NW_ADMIN_COOKIE).'"'.$setFilter;
/**
 * Data
 */
$data  = $action->getData('all',$query.' order by id desc','');
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
        * Check 
        */ 
        checkAll();       
       /**
        * View users information
        */
        $('.view-det').click(function(){
                        
            /**
             * Check if its employer or job seeker 
             */
            var act = 'jason-user-cont';
            
            var wid = '639px';
            
            var hie = '395px';
            /**
             * Check if its Employer
             */
            if(($(this).attr('act'))==2)
            {
                act = 'jason-emp-cont';
                
                wid = '685px';
                
                hie = '485px';
            }
            /**
             * Jason Data 
             */
            var info = { 
                          id  : $(this).attr('pid'),
                          key : act 
                       };
            /**
             * Ajax process 
             */          
            $.ajax({
                       url      : '<?php echo NW_DEFURL.NW_JAVA.'/nw-load.php'?>',
                       type     : 'POST',
                       data     :  info,
                       dataType : 'json',             
                       success  : function(result){
                                  
                                  if(result.success==1)
                                  {   
                                      var display = {content : result.content};
                                      
                                      iblynks({out :display,width:wid,height:hie,type:'header',title:result.header});  
                                  }
                                  else
                                  {
                                      nw_app_msg('An erro occured please try agin later',false); 
                                  }
                         }   
                    });

            
            
        });
        /**
         * Secure login to users acount
         */
        $('.access-acnt').click(function(){
                /**
                 * Light box display & variables
                 */
                iblynks({
                           out    : '<?php echo compress_page($jhtml->verifyBut('Are you sure you want to login to <b>users</b> account'))?>',
                           width  : '395px',
                           height : '215px',
                           type   : 'warning'
                       });
                       
                var userId  = $(this).attr('sec'); // Users security number
                
                var userCat = $(this).attr('cat'); // Users category (Emloyer or jobseeker)
                
                /**
                 * Yes Delete
                 */
                $('.yes-button').click(function(){
                    
                   window.open('../nw-secure.php?userid='+userId+'&category='+userCat,'_blank');
                   iblynks_close();
                   
                });
                /**
                 * No dont login
                 */
                $('.no-button').click(function(){

                    iblynks_close();

                });
           
        });
       /**
        * Delete user(s)
        */
        $('.del-users').live('click',function(){
            
                var cbox    = $('.cl:checked');
                /**
                 * Check if at least one job is checked
                 */
                var check   = cbox.length;
            
                if(check>0)
                {
                     $('.process-loading').show(); 

                     var ids  = mapElem('.cl:checked');

                     var info = { type : 'delete_users',data : ids };

                     $.ajax({
                              url  : '<?php echo NW_DEFURL.NW_JAVA.'/nw-del.php'?>',
                              type : 'POST',
                              data : info,
                              success : function(result){

                                           if(result==1)
                                           {
                                               window.location.replace('<?php NW_ADMIN_URL.'?nav=nw-admin-users'?>');
                                           }
                                           else
                                           { 
                                               nw_admin_alt('Cannot delete please try again later',true);
                                               $('.process-loading').hide(); 
                                           } 

                               }
                          });
                }
                else
                {
                      nw_admin_alt('Please select at least one user to <br/><br/><b>delete</b>',false);
                }
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
    <page><span>&raquo;</span>Manage Users</page>
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
                              <a  name='new-job' class='admin-button-one del-users' act='new' >
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
                        <select name='filter'>
                            <option value='2' <?php echo selected(2,$posts['filter']); ?>>
                                BY EMPLOYER
                            </option>
                            <option value='3' <?php echo selected(3,$posts['filter']); ?>>
                                BY JOB SEEKER
                            </option>      
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
                           <th>Full name</th>
                           <th>E-mail</th>
                           <th>Category</th>
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
                                   $category   = ($fetch['category']==2)? '<span style="color:green">Employer</span>': '<span style="color:blue">Job Seeker</span>';
                                 
                                   
                           ?> 
                                    <tr>
                                        <td>
                                           <center> 
                                              <input type='checkbox' id='checkbox-1-<?php echo $cat;?>' class='admin-checkbox cl' value='<?php echo $fetch['id']?>'> <label for='checkbox-1-<?php echo $cat;?>'></label> 
                                            </center>
                                        </td>
                                        <td><?php echo ucwords($fetch['fullname'])?></td>
                                        <td><?php echo ucwords($fetch['email'])?></td>
                                        <td><?php echo $category ?></td>
                                        <td width='13%'>
                                            <table width='100%' class='table_actions'>
                                               <tr>
                                                   <td class='view view-det' title='View details '
                                                      pid='<?php echo $fetch['id']; ?>'
                                                      act='<?php echo $fetch['category']?>'>
                                                   </td>
                                                   <td class='change-pswd access-acnt' title='Access users account'
                                                      usr='<?php echo $fetch['email']?>' 
                                                      sec='<?php echo $fetch['security']?>'
                                                      cat='<?php echo $fetch['category']?>'>
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
