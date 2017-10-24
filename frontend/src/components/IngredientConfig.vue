<template>
  <v-container>
    <v-layout row>
      <v-flex xs2>
        P {{item.id}}
      </v-flex>
      <v-flex xs6>
        <v-select
          v-bind:items="items"
          v-model="e1"
          label="Valve"
          single-line
          bottom
        ></v-select>
      </v-flex>
    </v-layout>
  </v-container>
</template>

<script>
export default {
  name: 'ingredientConfig',
  props: [
    'item'
  ]
}
</script>

<style>
</style>
