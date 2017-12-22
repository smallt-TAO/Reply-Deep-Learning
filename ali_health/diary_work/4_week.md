##20171218
public class App 
{
    public static void main( String[] args ) throws Exception {
        System.out.println( "Hello AliNLP bootstrap!" );

        // SentimentAnalysisHSFClient hsfClient = new SentimentAnalysisHSFClient("ykc_content_emotion", "ws_test");
        SentimentAnalysisHSFClient hsfClient = new SentimentAnalysisHSFClient("ykc_content_emotion", "sa_sentiment_100");
        String result1 = hsfClient.getResult("这衣服真难看");
        System.out.println(result1);

        IPClient ipClient = new IPClient("cco_ws", "ws_test");
        String result2 = ipClient.getResult("我爱自然语言处理和机器学习，我是NLPer");
        System.out.println(result2);

        String result3 = AlinlpWordSeg.wordSeg("我爱自然语言处理和机器学习");
        System.out.println(result3);

    }
}

##20171219
ODPS SQL mapjoin
optimization the sql code

##20171221
diaodu the jiedian 
ODPS SQL
bushuju

##20171222
tongji the data
