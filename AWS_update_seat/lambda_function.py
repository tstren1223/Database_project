import json
from  up_date_seat_table import *
def lambda_handler(event, context):
    # TODO implement
    connect()
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
}
