 /*game js*/
 function gameOrder_price(){
    item_value=document.order.game.value;
    qty_ordered=document.order.gameQty.selectedIndex;
    itemorderedprice=item_value*qty_ordered;
    tax=item_value*qty_ordered*0.05;
    document.order.gameSub1.value=itemorderedprice.toFixed(2);
    document.order.gameSub2.value=tax.toFixed(2);
    gameSubtotal_price();
}

function game_shipping_price(field){
    document.order.gameSub3.value=field.value; 
    gameSubtotal_price();
}

function gameSubtotal_price(){
    s1=parseFloat(document.order.gameSub1.value);
    s2=parseFloat(document.order.gameSub2.value);
    s3=parseFloat(document.order.gameSub3.value);

    gameSubtotal=s1+s2+s3;
    document.order.gameSubtotal.value=gameSubtotal.toFixed(2);
    total_price();
}

/*giftcard js*/
function giftcardOrder_price(){
    item_value=document.order.giftcard.value;
    qty_ordered=document.order.giftcardQty.selectedIndex;
    itemorderedprice=item_value*qty_ordered;
    tax=item_value*qty_ordered*0.05;
    document.order.giftcardSub1.value=itemorderedprice.toFixed(2);
    document.order.giftcardSub2.value=tax.toFixed(2);
    giftcardSubtotal_price();
}

function giftcard_shipping_price(field){
    document.order.giftcardSub3.value=field.value; 
    giftcardSubtotal_price();
}

function giftcardSubtotal_price(){
    s1=parseFloat(document.order.giftcardSub1.value);
    s2=parseFloat(document.order.giftcardSub2.value);
    s3=parseFloat(document.order.giftcardSub3.value);

    giftcardSubtotal=s1+s2+s3;
    document.order.giftcardSubtotal.value=giftcardSubtotal.toFixed(2);
    total_price();
}

/*Total js*/
function total_price() {
    t1=parseFloat(document.order.gameSubtotal.value);
    t2=parseFloat(document.order.giftcardSubtotal.value);

    total=t1+t2;
    document.order.total.value=total.toFixed(2);
}