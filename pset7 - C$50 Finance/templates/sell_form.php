<div>
    <ul id="nav_main">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php" id="current_page">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="change_password.php">Change Password</a></li>
        <li><a href="logout.php">Logout</a></li>
    </ul>
</div>
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select autofocus class="form-control" name="sell_choice" />
                <?php 
                print("<option value></option>");
                foreach($stocks as $stock)
                {
                    print("<option value=\"{$stock['symbol']}\">{$stock['symbol']}</option>");
                }
                ?>
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
