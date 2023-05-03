<?php
  require '../scripts/config.php';

  $database = "Toonify";
  $sql = "CREATE DATABASE if not exists $database";
  mysqli_query($conn,$sql);

  mysqli_select_db($conn, $database);
  $sql = "CREATE TABLE if not exists Requests (
          id int(11) NOT NULL AUTO_INCREMENT,
          image LONGBLOB NOT NULL,
          PRIMARY KEY (id)
      )";

  if (!mysqli_query($conn,$sql) === TRUE) {
  echo "Error creating table: " . $conn->error;
  }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <script src="https://kit.fontawesome.com/185669591d.js" crossorigin="anonymous"></script>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet"  href="../css/main.css?<?=time()?>">
    <title>Document</title>
</head>
<body>
<form action="../scripts/upload.php?>" method="post" enctype="multipart/form-data">
    <div class="container">
        <h1>Toonify</h1>
        <p>With Toonify, we'll take your images and make them into intricate cartoonified images — all with just a few clicks. To start, just upload a file of type png or jpeg and hit Toonify! We'll take care of the rest and you'll see the toonified version pop up just a few moments later❗</p>
        <div class = "buttons">              
              <label class="custom-file-upload">
                  <input type="file" name="image">
                  Upload
                  <i class="fa fa-cloud-upload" id="upload-icon" aria-hidden="true"></i>
              </label>
              <input class="custom-file-upload" type="submit" value="Toonify!" name="submit" />

              <?php 
                if (isset($_GET['error'])){
                  echo "<p id=\"error-message\">";
                  echo $_GET['error'];
                  echo "</p>";
                } 
              ?>
        </div>
    </div>
    </form> 
</body>
</html>

<!-- 

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/main.css?<?php echo rand(0,999);?>">
    <title>Document</title>
</head>
<body>
    <h1>

        #Checks for non-duplicate username
        function validateNonDuplicate($conn){
          $errors = false;
          $username = $_POST['Username'];
          $sql = "SELECT * FROM users WHERE username = '$username'";
          $result = mysqli_query($conn, $sql);

          if(mysqli_num_rows($result) > 0){
            $errorMessage = "That username is already in use. Please choose a different one or login <a class = \"errorRedirect\" href=\"login.php\">here</a>";
            $errors = true;
            }

          //   Employee is not found
          else{
            $firstName = $_POST['First_Name'];
            $lastName = $_POST['Last_Name'];
            $email = $_POST['Email'];
            $username = $_POST['Username'];

            $password = md5($_POST['Password']);

            $sql = "INSERT INTO users(firstname, lastname, email, username, password, attempts)
                    VALUES ('$firstName', '$lastName', '$email', '$username', '$password', 0)";

            mysqli_query($conn, $sql);
            }



          if($errors){
            echo "<p class = \"error\">$errorMessage</p>";
          }else{
            return true;
          }
        }

        if(isset($_POST['Register'])){
          $fields = array('First_Name','Last_Name','Email','Username','Password','Confirm_Password');
          if(validateFilled($fields)){
            if(validateFields()){
              if(validateNonDuplicate($conn)){
                #Redirects user to quiz page after 3 seconds or if pressed
                echo "<p class = \"success\">Successfully Registered. Click <a class = \"success\" href=\"homepage.php\">here</a> to go to the <a class = \"success\" href=\"homepage.php\">quiz page</a> or wait 3 seconds to be automatically redirected</p>";
                header( "refresh:3;url=homepage.php" );

                $_SESSION['Username'] = $_POST['Username'];
              }
            }
          }
        }

        ?>

    </h1>
</body>
</html>
 -->
<?php
 if(isset($_POST["submit"])){ 
    $status = 'error'; 
    if(!empty($_FILES["image"]["name"])) { 
        // Get file info 
        $fileName = basename($_FILES["image"]["name"]); 
        $fileType = pathinfo($fileName, PATHINFO_EXTENSION); 
         
        // Allow certain file formats 
        $allowTypes = array('jpg','png','jpeg','gif'); 
        if(in_array($fileType, $allowTypes)){ 
            $image = $_FILES['image']['tmp_name']; 
            $imgContent = addslashes(file_get_contents($image)); 
         
            // Insert image content into database 
            $insert = $db->query("INSERT into images (image, created) VALUES ('$imgContent', NOW())"); 
             
            if($insert){ 
                $status = 'success'; 
                $statusMsg = "File uploaded successfully."; 
            }else{ 
                $statusMsg = "File upload failed, please try again."; 
            }  
        }else{ 
            $statusMsg = 'Sorry, only JPG, JPEG, PNG, & GIF files are allowed to upload.'; 
        } 
    }else{ 
        $statusMsg = 'Please select an image file to upload.'; 
    } 
} 
 ?>