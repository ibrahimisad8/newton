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
 * General Class
 */
$action = new snSystem();
/**
 * Get Posts
 */
$posts  = sn_process_post();
/**
 * Show search result
 */
$search = array();
//Result
$search['result'] = false;
//Result message
$search['msg']    = "<img class='s-img' src='".NW_IMAGE_URL."general/search.png' />";
/***
 * Countries list
 */
$country_list = counties_list('custom','',1);
/***
 * Countries list
 */
$industry_list = industry_list('',1);
/**
 * Search data base
 */
if(isset($posts['job-search']))
{
    if(!empty($posts['keyword']))
    {   
        $posts_key = '';
 
        $onkeyword = $onindust = false;
        /**
         * Check Keyword
         */
        if($posts['keyword']!=='Keyword, Job title')
        {   
            $posts_key   = '<span class="raq">&raquo;</span> <b>'.$posts['keyword'].'</b>';
            $keyword     = ' where job_title like("' .$posts['keyword']. '%")';
            $onkeyword   = true;
        }
        /**
         * Check industry
         */
        if(!empty($posts['industry'])&&$posts['industry']!=='NULL')
        {   
            $posts_key .=' <span class="raq">&raquo;</span> <b>'.$industry_list[$posts['industry']].'</b>';
            $andwhere   = ($onkeyword==true)? ' and':' where'; 
            $industry   = $andwhere.' industry like("'.$posts['industry'].'")';
            $onkeyword  = true;
        }
        /**
         * Check country
         */
        if(!empty($posts['country'])&&$posts['country']!=='NULL')
        {   
            $posts_key .=' <span class="raq">&raquo;</span> <b>'.$country_list[$posts['country']].'</b>';
            $andwhere   = ($onkeyword==true)? ' and':' where';
            $country    = $andwhere.' country like("'.$posts['country'].'")';
        }        
       /**
        * Search data
        */
       $data = $action->getData('all','select * from nw_jobs'.$keyword.$industry.$country.' order by id desc');
       
       if($data['count']>0)
       { 
           $search['result']= true;    
       }
       else
       {
           $search['msg']   = "
                                <p>
                                   <img class='s-img' src='".NW_IMAGE_URL."general/empty-two.png' />
                                </p>
                                <p>
                                   No <b>result</b> found
                                </p>
                               ";
       }
    }
}

?>
<script>
    $(function(){
        /**
         * Process search
         **/        
        $('[name="job-search"]').click(function(){
           
                /**
                 * Inputs for new link
                 **/
                var hDl  = Array('keyword');
                /**
                 * Error Message
                 **/
                 var mSg = new Array;
                 
                 mSg[hDl[0]] = 'Please enter keyword';
                 
                 if(process_input(hDl,mSg,'')==false)
                     
                 return false;
                 
                 else
           
                 generalLoaDiv('show','.generalFadediv','.hold-jquery');
           
        });
    });
</script>

<?php DynDiv('H','Jobs Search');?>

    <div class='general-content'>
        <div class='generalFadediv genFadediv-border-radius'></div>    
        <div class='hold-jquery'>
            <div class='inputs-job-hold'>
                <form action='#' method='post'>
                    <p>
                        Go through our job inventory and get the right job you want
                    </p>
                    <p>
                        <input type='text' name='keyword' class='test' p='italic' /> 
                        <select name='industry'>
                            <option value='NULL'>Select all Industries</option>
                            <?php industry_list($posts['industry'],false) ?>
                        </select>
                        <select name='country'>
                            <option value='NULL'>Select all locations</option>
                             <?php counties_list('custom',$posts['country'],false)?>
                        </select>
                        <button type='submit' name='job-search' class='com' >Search</button> 
                    </p>
                </form>
            </div>
            <div class='the-search'>
                <div class='top-content'>
                    <?php if($search['result']==false):?>
                    <div style='padding:25px 0px;'>
                        <center>
                            <?php echo $search['msg'];?>
                        </center>
                    </div>
                    <?php else:?>

                        <div class='search-result'>
                            <div class='job-count'>
                                <?php 
                                      $s = ($data['count']>1)?"s":"";
                                      $posts_key = (!empty($posts_key))? $posts_key :' <b>in our database</b>';
                                      echo "Total of <b>".$data['count']."</b> job".$s." found ".$posts_key;
                                 ?>
                             </div>
                            <?php 

                               while($result = mysql_fetch_assoc($data['query']))
                               {   
                                   $company = $action->getData('array','select * from nw_organization where employer="'.$result['employer_id'].'" '); 

                                   echo "<div class='result-child'>
                                           <table width='100%'>
                                           <tr>
                                               <td width='85%' valign='top'>
                                                  <p id='job-title'>
                                                        <a href='?nav=nw-viewjob&id=".$result['id']."&msc=1' class='url'> 
                                                          <span> ".$result['job_title']."</span><br/>
                                                          <span id='country'>".$company['company']." - ".$company['state']." - ".$country_list[$company['country']]."</span>
                                                       </a>
                                                  </p>
                                                  <p id='job-desc'>".disp_let($result['job_description'])."</p>
                                               </td>
                                               <td width='5%'></td>
                                               <td valign='top'>
                                                 <p style='line-height:1.5em'> ".sn_date('change',7,$result['date'])."</p>
                                               </td>
                                           </tr>
                                           </table>
                                        </div>";
                               }

                            ?>
                        </div>
                    <?php endif; ?>
                </div>
            </div>
        </div>
    </div>

<?php DynDiv('F','');?>

