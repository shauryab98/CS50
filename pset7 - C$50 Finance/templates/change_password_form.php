<div>
    <ul id="nav_main">
        <li><a href="index.php" >Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="change_password.php" id="current_page">Change Password</a></li>
        <li><a href="logout.php">Logout</a></li>
    </ul>
</div>
<form action="change_password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="curr_password" placeholder="Current password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_password" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirm_new_password" placeholder="Password again" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Change password</button>
        </div>
    </fieldset>
</form>
