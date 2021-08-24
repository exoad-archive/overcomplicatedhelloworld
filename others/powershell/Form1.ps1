if($global:apiLimit -eq $null){
    $global:apiLimit = 0;
}

function translate([string][Parameter(valueFromPipeline=$true)]$text, $sourceLanguage, $targetLanguage){
    if($sourceLanguage -eq $targetLanguage){
        return $text; #Smartarse
    }

    if($accessToken -eq $null -or (([datetime]::now - $accessTokenTime).totalMinutes -ge 10)){
        #Azure access tokens last for 10 minutes
        $accessTokenTime = [datetime]::now;
        $accessTokenResponse = irm -method post -body @{
            client_id = 'blah'; #Go sign up for the Microsoft Translate API yourself if you are weird enough to actually run this
            client_secret = 'blah'; #I'm not going to actually leave my key in here
            scope = 'http://api.microsofttranslator.com';
            grant_type = 'client_credentials';
        } -uri https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/;
        $accessToken = $accessTokenResponse.access_token;
    }

    if(($global:apiLimit += $text.length) -ge 2e6){
        #Sleep for one whole month because you have to sign up for a paid subscription to get more than 2M chars or some shit
        sleep (get-date).addMonths(1).subtract((get-date)).totalSeconds
    }
    $url = "http://api.microsofttranslator.com/v2/Http.svc/Translate?text=$([Uri]::escapeDataString($text))&from=$([Uri]::escapeDataString($sourceLanguage))&to=$([Uri]::escapeDataString($targetLanguage))";
    $response = invoke-restMethod $url -headers @{Authorization = "Bearer $accessToken"};
    return $response.string.innerText;
}

function isHelloWorld([string][Parameter(valueFromPipeline=$true)]$s){
    #This function sucks but I had a few beers so what you gonna do about it
    switch -regex ($s -ireplace '[^\sA-Z]', ''){
        <#Translation engine might decide to return 'Hello, world!' 'Hello world!' 'Hello world' 'Hello world program' 'Hello everyone' and who 
        knows what else depending on what I use (Yandex and MyMemory are especially stupid) so just strip out everything but words and spaces#>
        '^Hello\s+(world|everyone)(\s+program)?$'{
            return $true;
        }
        default {
            return $false;
        }
    }
}

#$target = 'こんにちは 世界' #Konnichiwa sekai
#translate $target ja en | isHelloWorld

function makeRandomJapaneseString($length){
    $sb = new-object Text.StringBuilder;
    $hiraganaRange = 0x3041..0x3093; #There are a few more up to 309f but those ones are weird so who cares
    #Katakana is not used for this purpose
    $kanjiRange = 0x4e00..0x9faf;
    #Ignore the extended kanji because it looks like the kanjis in 'world' are in the normal range anyway

    0..($length - 1) | % {
        [void]$sb.append([char]($hiraganaRange + $kanjiRange | get-random));
    }
    return "$sb";
}

do {
    $english = makeRandomJapaneseString 7 | translate -source ja -target en
    write-debug $english #Most likely some random bullshit
} until (isHelloWorld $english);
