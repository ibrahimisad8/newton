<?php
/**
 * General Class
 * 
 * This file is important to all pages changes can be made to constants if  the 
 * need arises
 * @author Ibrahim Isa
 * @version 1.0
 * @package modules.connection
 * @link http://www.iblynks.com
 */

class dbConnect extends config 
{

    /**
     * Php constructor
     */
    function __construct() 
    {
        // connecting to database
        $this->connect();
    }
    /**
     * Php Destructor
     */
    function __destruct()
    {
        // closing db connection
        $this->close();
    }
    /**
     *  Connect to the database
     */
    function connect() 
    {		
               
       
        $host     = $this->host;
        $user     = $this->db_local_user;
        $password = $this->db_local_pswd;
        $database = $this->db_local_base ;
        $con      = mysql_connect($host,$user, $password);
        $select   = mysql_select_db($database);
        
 
         /**
         * Connecting to mysql database 
         */
        if(!$con||!$select) 
        {  
          header('location:'.NW_DEFURL.'error/?action=connect_error');
           
        }
       
        return $con;
    }
    /**
     * Function to close db connection
     */
    function close() 
    {
        /**
         * closing db connection
         */
        mysql_close();
    }

}

class snSystem
{   
   /**
    * This holds the first variable infromation or data
    * @access private
    * @var string|integer
    */   
    private $varone ;
   /**
    * Second variable infromation or data
    * @access private
    * @var string|integer
    */ 
    private $vartwo ;
   /**
    * Third variable infromation or data
    * @access private
    * @var string|integer
    */ 
    private $varthr ;
   /**
    * HTTP url variable infromation or data
    * @access private
    * @var string|integer
    */ 
    private $url;

    /**
     * @param  string  $data
     * @param  string $type
     * @param  string $column
     * @return array
     * Description : General Mysql function 
     */
    private function mysql_fetch_update($data,$type,$column)
    {

          $db = new dbConnect();

          switch($type)
          {	  

                /*----------------------------------------------------------------------------*/
                /*                           Max id for databse table                         */
                /*----------------------------------------------------------------------------*/

                case 'max-col':

                    $query  = mysql_query($data);

                    $fetch  = mysql_fetch_assoc($query);

                    $select = $fetch['MAX(id)'] + 1;

                break;

               /*----------------------------------------------------------------------------*/
               /*                           return single column by row                      */
               /*----------------------------------------------------------------------------*/

                case 'ret-one':

                    $query  = mysql_query($data);

                    $fetch  = mysql_fetch_assoc($query);

                    $select = $fetch[$column];

                break;

               /*----------------------------------------------------------------------------*/
               /*                           Count the number of rows                         */
               /*----------------------------------------------------------------------------*/

                case 'count'  :

                    $query = mysql_query($data);

                    $select= mysql_num_rows($query);

                break;

                default:$select = mysql_query($data);
        }


          return $select;	

    }
    /**
     * @return variable character | string
     * 
     * This function generates radom charcter both numbers abd letters
     * MAX - 32
     * MIN - 9
     */
    public function randoms()
    {

            /**
             *  Define random charcters with array
             */
            $characters = array("a","b","c","d","e","f","g","h","i","j","k","l",

                                "M","N","O","p","q","r","S","t","u","V","w","Z",

                                "1","2","3","4","5","6","7","8","9");
            /**
             * make an "empty container" or array for our keys
             */
            $keys = array();
            /**
             * first count of $keys is empty so "1", remaining count is 1-6 = total 7 times
             */
            while(count($keys) < 32 ) 
            {
                /**
                 * "0" because we use this to FIND ARRAY KEYS which has a 0 value
                 * "-1" because were only concerned of number of keys which is 32 not 33
                 * count($characters) = 33
                 */
                $x = mt_rand(0, count($characters)-1);

                if(!in_array($x, $keys))
                { 
                    $keys[] = $x;
                }

            }

            foreach($keys as $key){ $random_chars .= $characters[$key]; }


            return $random_chars;
    } 
    /**
     * Description : Insert Data Into The database using Array Values passed 
     * @param  string $table
     * @param  array  $inserts
     * @return Bool
     */
    public function ib_insert_data($table, $inserts) 
    {

       $values = array_map('mysql_real_escape_string', array_values($inserts));

       $keys   = array_keys($inserts); 

       $out    = $this->mysql_fetch_update('INSERT INTO `'.$table.'` (`'.implode('`,`', $keys).'`) VALUES (\''.implode('\',\'', $values).'\')');

       return $out;

    }
    /**
     * @param  array  $table
     * @param  string $array
     * @param  string $cond
     * @return bool
     */
    function ib_update_data($table,$array,$cond) 
    {
           if (count($array) > 0) 
           {
               foreach ($array as $key => $value) 
               {
                   $value     = mysql_real_escape_string($value);
                   $val       = "'$value'";
                   $updates[] = "$key = $val";
               }
           }

           $impld = implode(', ', $updates);

           $sql   = "update ".$table."  set $impld ".$cond." ";

           if($this->mysql_fetch_update($sql)) 
           { 
               $set  = true; 
           }

           return $set;

    }
    /**
     * @param  array  $array
     * @param  string $table
     * @param  string $cond
     * @return bool
     */
    function ib_delete_data($sql) 
    {

           if($this->mysql_fetch_update($sql)) 
           { 
               $set  = true; 
           }

           return $set;

    }
    /**
     * Description : MySql query (Update,delete,select e.t.c)
     * @param string $option type of execution
     * @param string $av1 sql syntax
     * @param string $av2 return one data
     * @return string|array
     */    
    public function getData($option,$av1,$av2)
    {   
        /**
         * Mysql Query
         */
        $this->varone  = $av1;
        /**
         * Get data base data as array
         */
        if($option=='array')
        {    

               $this->vartwo  = $this->mysql_fetch_update($this->varone);
               
               $this->varone  = mysql_fetch_assoc($this->vartwo);

               return  $this->varone;

        }
        /**
         * Return Mysql single data from row in respect to
         * row
         */        
        if($option=='single')
        {

              $this->vartwo  = $this->mysql_fetch_update($this->varone,'ret-one',$av2);

              return $this->vartwo;
        }
        /**
         * Count number of data in the data base
         */        
        if($option=='count')
        {

              $this->vartwo  = $this->mysql_fetch_update($this->varone,'count','');

              return $this->vartwo;
        }
        /**
         * Count number of data in the data base
         */        
        if($option=='max-col')
        {

              $this->vartwo  = $this->mysql_fetch_update($this->varone,'max-col','');

              return $this->vartwo;
        }
        /**
         * Count number of data in the data base
         */        
        if($option=='query')
        {

              $this->vartwo  = $this->mysql_fetch_update($this->varone,'','');

              return $this->vartwo;
        }
        /**
         * Set and get all datas
         */
        if($option=='all')
        {   
            /**
             * select the query
             */
            $select = $this->mysql_fetch_update($this->varone);
            /**
             * Count the data
             */
            $count  = mysql_num_rows($select);
            /**
             * Fetch the data for single row 
             */
            $fetch  = mysql_fetch_assoc($this->mysql_fetch_update($this->varone));
            /**
             * Set the data in array
             */
            $system = array(
                             'query' => $select,
                             'count' => $count,
                             'fetch' => $fetch
                           );
            
            return $system;
        }

   }
   
    /**
     * Description : This function set global PHP browser cookie
     *  
     * @param string|integer $group
     * @param string|integer $cookie 
     * @param string|integer $default usualy HTTP url
     */
    public  function set_cook_user($group,$cookie,$default)
    {
          $path = new config();
          
          define("DEFAULT_PAGE",NW_DEFURL.$default);
          /**
           * Login & logout user
           */
          if($group=='exit')
          {
                  setcookie("$cookie", "", time()-+60*60*60,$path->no_root());
                  
                  header('location:'.DEFAULT_PAGE);  
          }else{
             
                  setcookie("$group", "$cookie", time()+60*60*60,$path->no_root());
                  
                  if($default!=='null')
                  {
                    header('location:'.DEFAULT_PAGE);
                  }
          }

          return true;

    }
}

class ea_comment
{   
   /**
    * This holds the first variable infromation or data
    * @access private
    * @var integer
    */ 
    private  $return = 0;
    /**
     * Description : General Mysql function
     * @return integer 
     */
    protected function check_user_logeIn()
    {                   
        $admin = filter_input(INPUT_COOKIE,NW_ADMIN_COOKIE);
        
        $user  = filter_input(INPUT_COOKIE,NW_EMPLOYEE_COOKIE);
        
        if(isset($admin))
        {
            $this->return = 1;
        }
        elseif(isset($user))
        { 
            $this->return = 2;  
        }
        return $this->return;
    }
    /**
     * Description : Get the users cookie 
     * @return string 
     */
    protected function user_cookie()
    {   
        $user = $this->check_user_logeIn();
        
        if($user==2)
        {
            $this->return = filter_input(INPUT_COOKIE,NW_EMPLOYEE_COOKIE);
        }
        elseif($user==1)
        {
            $this->return = filter_input(INPUT_COOKIE,NW_ADMIN_COOKIE);
        }
        
        return $this->return;
    }
    /**
     * Description : Get & check Comments
     * @return integer
     */
    protected function handle_comment($type,$job_id)
    {    
         $action = new snSystem();
         $SQL    = 'select * from nw_comments where job_id="'.$job_id.'"';
         // Check Post        
         if($type=='check')
         {  
            //$cookie = $this->user_cookie();
            $query  = $SQL;
            $check  = $action->getData('count',$query,'');
            $this->return = $check;
         }
         // Get comments
         if($type=='get-comment')
         {                
             $query = $action->getData('query',$SQL,'');
             
             $com_new ="";
             
             while($data = mysql_fetch_assoc($query))
             {   
                 // Class id for deleting comment
                 $cid  = 'com_'.$data['id'];
                 // Date posted comment
                 $date = sn_date('change',3,$data['date']);
                 // The comment
                 $comment = $data['comment'];
                 // Delete button
                 $spd  = "<span class='del-x' title='Delete comment' p='".$data['id']."' cid='".$cid."'></span>";
                 $span = "";
                 // Set employer or admin class & user
                 // Possible testing use "$query" instead of "$sq"
                 if($data['user']==2)
                 {
                     $class   = 'employer';
                     $sq      = 'select * from nw_users where security="'.$data['user_id'].'"';
                     $dbData  = $action->getData('array',$sq);
                     $user    = ucwords($dbData['fullname']);
                     if($this->return_user_cookie()==$data['user_id'])
                     {
                       $span = $spd;  
                     }
                 }
                 elseif($data['user']==1)
                 {
                     $class   = 'admin';
                     $user    = 'Administrator';
                     if($this->return_user_cookie()==$data['user_id'])
                     {
                       $span = $spd;  
                     }
                 }
                 // Return Comments
                 $com_new.="
                             <div class='".$class."' id='".$cid."'>
                                    ".$span."
                                      <span>
                                        <b>".$user." : </b> 
                                        <span style='font-size:11px'>Posted on ".$date."</span>
                                      </span>
                                    <p>
                                       ".$comment."
                                    </p>
                                 </div>
                            ";
              }
              
              $this->return = $com_new;
         }
         return $this->return;
        
    }
    /**
     * Deacription : Check post
     * @return integer 
     */
    public function check_post($job_id)
    {
        
        $data  = $this->handle_comment('check',$job_id);
        
        return $data;
    }
    /**
     * Description : Return User Cookie
     * @return string return users cookie session
     */
    public function return_user_cookie()
    {
        return $this->user_cookie();
    }
    /**
     * Description : Logged In User (Admin or Employer)
     * @return integer
     */
    public function logedin_user()
    {
       return $this->check_user_logeIn();         
    } 
    /**
     * Description : Return Comments
     */
    public function get_comments($job_id)
    {
        return $this->handle_comment('get-comment', $job_id);
    }
}


